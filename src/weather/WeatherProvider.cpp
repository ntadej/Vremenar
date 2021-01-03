/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QBuffer>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtGui/QImage>

#include "common/NetworkManager.h"
#include "settings/Settings.h"
#include "weather/WeatherProvider.h"
#include "weather/api/APIMapLayers.h"
#include "weather/api/APIStations.h"
#include "weather/containers/MapInfo.h"

namespace
{
constexpr uint32_t INTERVAL = 300000;
constexpr uint32_t PROTECTION = 60000;
} // namespace

namespace Vremenar
{

WeatherProvider::WeatherProvider(NetworkManager *network,
                                 QObject *parent)
    : APILoader(network, parent),
      _currentWeather(std::make_unique<CurrentWeather>(this)),
      _weatherMapModelBase(std::make_unique<WeatherMapModel>(this)),
      _weatherMapModel(std::make_unique<WeatherMapModel>(this)),
      _weatherMapProxyModel(std::make_unique<WeatherMapProxyModel>(this)),
      _mapInfoModel(std::make_unique<MapInfoModel>(this)),
      _mapLayersModel(std::make_unique<MapLayersModel>(this)),
      _mapLayersProxyModel(std::make_unique<MapLayersProxyModel>(this)),
      _mapLegendModel(std::make_unique<MapLegendModel>(this)),
      _mapLegendProxyModel(std::make_unique<MapLegendProxyModel>(this)),
      _timer(std::make_unique<QTimer>(this)),
      _timerCurrent(std::make_unique<QTimer>(this))
{
    Settings settings(this);
    if (settings.weatherSource() == Sources::Germany) {
        _supportedMapTypes = {
            Weather::WeatherConditionMap,
            Weather::PrecipitationMap};
        _copyrightLink = std::make_unique<Hyperlink>(
            QStringLiteral("© Deutscher Wetterdienst"),
            QStringLiteral("https://dwd.de"));
    } else {
        _supportedMapTypes = {
            Weather::WeatherConditionMap,
            Weather::PrecipitationMap,
            Weather::CloudCoverageMap,
            Weather::WindSpeedMap,
            Weather::TemperatureMap,
            Weather::HailProbabilityMap};
        _copyrightLink = std::make_unique<Hyperlink>(
            QStringLiteral("© ") + tr("Slovenian Environment Agency"),
            QStringLiteral("https://www.arso.gov.si"));
    }

    weatherMap()->setSourceModel(_weatherMapModel.get());
    mapInfo()->generateModel(supportedMapTypes());
    mapLayers()->setSourceModel(_mapLayersModel.get());
    mapLegend()->setSourceModel(_mapLegendModel.get());

    connect(mapLayers(), &MapLayersProxyModel::timestampChanged, this, &WeatherProvider::currentTimeChanged);

    _timer->setSingleShot(true);
    _timerCurrent->setSingleShot(true);

    connect(_timer.get(), &QTimer::timeout, this, &WeatherProvider::timerCallback);
    connect(_timerCurrent.get(), &QTimer::timeout, this, &WeatherProvider::timerCallbackCurrent);

    if (settings.startupMapEnabled()) {
        changeMapStyle(settings.startupMapStyle());
    } else {
        changeMapStyle(Weather::MapStyle::SatelliteMapStyle);
    }
}

void WeatherProvider::requestCurrentWeatherInfo(const QGeoCoordinate &coordinate)
{
    stopTimerCurrent();

    if (coordinate.isValid()) {
        qDebug() << "Requesting current weather details:" << coordinate;
        APIRequest request = API::stations(coordinate);
        currentReplies()->insert(network()->request(request), request);
    } else if (current()->hasStation()) {
        qDebug() << "Requesting current weather details:" << current()->station()->id();
        APIRequest request = API::stationWeatherCondition(current()->station()->id());
        currentReplies()->insert(network()->request(request), request);
    }
}

void WeatherProvider::requestBaseInfo()
{
    qDebug() << "Requesting base weather info";

    APIRequest request = API::mapLegends();
    currentReplies()->insert(network()->request(request), request);
}

void WeatherProvider::requestWeatherMapDetails(const QString &url)
{
    qDebug() << "Requesting weather details:" << url;

    setLoading(true);

    APIRequest request = API::stationsMap(url);
    currentReplies()->insert(network()->request(request), request);
}

void WeatherProvider::requestImage(const QString &url)
{
    qDebug() << "Requesting image:" << url;

    setLoading(true);

    APIRequest request = API::mapImage(url);
    currentReplies()->insert(network()->request(request), request);
}

void WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

    setLoading(true);

    mapLayers()->setUpdating(true);
    _weatherMapModelBase->clear();
    _weatherMapModel->clear();
    _mapLayersModel->clear();

    APIRequest request = API::mapLayers(type);
    currentReplies()->insert(network()->request(request), request);
}

void WeatherProvider::response(QNetworkReply *reply)
{
    if (!currentReplies()->contains(reply)) {
        return;
    }

    qDebug() << "Request done:" << reply->url() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    bool valid{};

    if (currentReplies()->value(reply).call() == QStringLiteral("/image")) {
        QImage image;
        image.loadFromData(reply->readAll());

        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG");
        QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());
        mapLayers()->setImage(QStringLiteral("data:image/jpeg;base64,") + iconBase64);
        mapLayers()->setUpdating(false, true);
        mapLayers()->playResume();

        removeResponse(reply);
        setLoading(false);
        return;
    }

    // JSON
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (currentReplies()->value(reply).call() == QStringLiteral("/maps/legend")) {
        const QJsonArray data = document.array();

        _mapLegendModel->clear();
        _mapLegendModel->addMapLegends(data);

        removeResponse(reply);
        return;
    }
    if (currentReplies()->value(reply).call() == QStringLiteral("/stations/coordinate")) {
        const QJsonArray stations = document.array();
        if (stations.empty()) {
            removeResponse(reply);
            return;
        }
        current()->setStation(StationInfo::fromJson(stations.first().toObject()));
        requestCurrentWeatherInfo(QGeoCoordinate());
        removeResponse(reply);
        return;
    }
    if (currentReplies()->value(reply).call() == QStringLiteral("/stations/condition")) {
        const QJsonObject weatherInfo = document.object();
        current()->updateCurrentWeather(WeatherCondition::fromJson(weatherInfo[QStringLiteral("condition")].toObject()));

        _lastUpdateResponseTimeCurrent = QDateTime::currentDateTime();
        startTimerCurrent();
        Q_EMIT lastUpdateTimeChangedCurrent();

        removeResponse(reply);
        return;
    }

    if (currentReplies()->value(reply).call() == QStringLiteral("/stations/map")) {
        _weatherMapModelBase->addEntries(document.array());
        if (currentReplies()->value(reply).url().toString().contains(QStringLiteral("current"))) {
            _weatherMapModel->addEntries(document.array());
        } else {
            _weatherMapModel->update(_weatherMapModelBase.get(), mapLayers()->timestamp());
        }
        mapLayers()->playResume();
        removeResponse(reply);
        valid = true;
    } else if (currentReplies()->value(reply).call() == QStringLiteral("/maps/list")) {
        auto type = Weather::MapType(currentReplies()->value(reply).extra().toInt());

        removeResponse(reply);

        mapLayers()->setUpdating(true);

        const QJsonObject data = document.object();

        auto reportedType = Weather::mapTypeFromString(data[QStringLiteral("map_type")].toString());
        if (reportedType == Weather::UnknownMapType || reportedType != type) {
            qDebug() << "Invalid map type " << reportedType << ", expected " << type;
            return;
        }

        _weatherMapModelBase->clear();
        _weatherMapModel->clear();
        _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(type, data);

        if (type == Weather::WeatherConditionMap) {
            currentTimeChanged();
            return;
        }

        valid = true;
    }

    if (!valid) {
        return;
    }

    mapLayers()->setUpdating(false);

    _lastUpdateResponseTime = QDateTime::currentDateTime();
    setLoading(false);
    startTimer();
    Q_EMIT lastUpdateTimeChanged();
}

void WeatherProvider::currentTimeChanged()
{
    if (mapLayers()->type() == Weather::TilesRendering) {
        mapLayers()->playResume();
        return;
    }

    if (currentType() != Weather::WeatherConditionMap) {
        requestImage(mapLayers()->url());
        return;
    }

    MapLayer *layer = _mapLayersModel->findLayer(Weather::WeatherConditionMap, mapLayers()->timestamp());
    if (layer == nullptr) {
        return;
    }

    mapLayers()->setImage(QStringLiteral("data:image/jpeg;base64,") + Weather::blankPng);

    if (!layer->loaded()) {
        requestWeatherMapDetails(layer->url().toString());
        layer->setLoaded();
    } else {
        _weatherMapModel->update(_weatherMapModelBase.get(), mapLayers()->timestamp());
        mapLayers()->playResume();
    }
}

bool WeatherProvider::currentMapLayerHasLegend() const
{
    return !(currentType() == Weather::WeatherConditionMap || currentType() == Weather::CloudCoverageMap || currentType() == Weather::UnknownMapType);
}

void WeatherProvider::changeMapStyle(Weather::MapStyle style,
                                     bool action)
{
    if (_currentStyle == style) {
        return;
    }

    if (action) {
        Q_EMIT recordEvent(Analytics::MapStyleChanged, Weather::mapStyleToString(style));
    }

    _currentStyle = style;

    Q_EMIT currentMapStyleChangedSignal(currentMapStyle());
    Q_EMIT storeState();

    qDebug() << "Map style changed" << style;
}

void WeatherProvider::changeMapType(Weather::MapType type,
                                    bool action)
{
    if (_currentType == type) {
        return;
    }

    if (action) {
        Q_EMIT recordEvent(Analytics::MapTypeChanged, Weather::mapTypeToString(type));
    }

    _currentType = type;
    _mapLegendProxyModel->setType(_currentType);

    Q_EMIT currentMapLayerChangedSignal(currentMapLayer());
    Q_EMIT currentMapLayerHasLegendChangedSignal(currentMapLayerHasLegend());

    _timer->stop();
    requestMapLayers(_currentType);

    Q_EMIT storeState();
}

void WeatherProvider::currentMapStyleChanged(int index)
{
    changeMapStyle(Weather::MapStyle(index + 1), true);
}

void WeatherProvider::currentMapLayerChanged(int index)
{
    if (index < 0 || index >= static_cast<int>(supportedMapTypes().size())) {
        return;
    }

    changeMapType(_mapInfoModel->row<MapInfo>(index)->type(), true);
}

int WeatherProvider::currentMapStyle() const
{
    if (_currentStyle == Weather::MapStyle::StreetsMapStyle) {
        return 1;
    }

    return 0;
}

int WeatherProvider::currentMapLayer() const
{
    const std::vector<Weather::MapType> &types = supportedMapTypes();
    auto it = std::find(types.begin(), types.end(), _currentType);
    return static_cast<int>(std::distance(types.begin(), it));
}

void WeatherProvider::refresh()
{
    _timer->stop();
    _timerCurrent->stop();

    requestMapLayers(_currentType);
    requestCurrentWeatherInfo(QGeoCoordinate());

    Q_EMIT storeState();
}

void WeatherProvider::startTimer()
{
    _timer->start(INTERVAL);

    qDebug() << "Autorefresh:"
             << "Starting timer...";
}

void WeatherProvider::startTimerCurrent()
{
    _timerCurrent->start(INTERVAL);

    qDebug() << "Autorefresh:"
             << "Starting current weather timer...";
}

void WeatherProvider::stopTimerCurrent()
{
    _timerCurrent->stop();
}

void WeatherProvider::timerCallback()
{
    _timer->stop();

    auto now = QDateTime::currentDateTime();
    if (_lastUpdateResponseTime.msecsTo(now) < PROTECTION) {
        qDebug() << "Autorefresh:"
                 << "Already requested information less than" << PROTECTION << "ms ago.";
        startTimer();
        return;
    }

    qDebug() << "Autorefresh:"
             << "Reloading...";

    _lastUpdateResponseTime = now;
    requestMapLayers(_currentType);

    Q_EMIT storeState();
}

void WeatherProvider::timerCallbackCurrent()
{
    _timerCurrent->stop();

    auto now = QDateTime::currentDateTime();
    if (_lastUpdateResponseTimeCurrent.msecsTo(now) < PROTECTION) {
        qDebug() << "Autorefresh:"
                 << "Already requested current weather information less than" << PROTECTION << "ms ago.";
        startTimer();
        return;
    }

    qDebug() << "Autorefresh:"
             << "Reloading current weather...";

    _lastUpdateResponseTimeCurrent = now;
    requestCurrentWeatherInfo(QGeoCoordinate());
}

void WeatherProvider::setLoading(bool loading)
{
    if (_loading != loading) {
        _loading = loading;
        Q_EMIT loadingChanged();
    }
}

void WeatherProvider::startupCompleted()
{
    Q_EMIT currentMapStyleChangedSignal(currentMapStyle());
}

} // namespace Vremenar
