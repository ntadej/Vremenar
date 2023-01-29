/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
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
#include "weather/api/APIAlerts.h"
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
      _stationsModel(std::make_unique<StationListModel>(this)),
      _stationsWithCurrentConditionModel(std::make_unique<StationListModel>(this)),
      _timer(std::make_unique<QTimer>(this)),
      _timerCurrent(std::make_unique<QTimer>(this))
{
    resetSource(false);

    weatherMap()->setSourceModel(_weatherMapModel.get());
    mapLayers()->setSourceModel(_mapLayersModel.get());
    mapLegend()->setSourceModel(_mapLegendModel.get());

    connect(mapLayers(), &MapLayersProxyModel::timestampChanged, this, &WeatherProvider::currentTimeChanged);

    _timer->setSingleShot(true);
    _timerCurrent->setSingleShot(true);

    connect(_timer.get(), &QTimer::timeout, this, &WeatherProvider::timerCallback);
    connect(_timerCurrent.get(), &QTimer::timeout, this, &WeatherProvider::timerCallbackCurrent);

    Settings settings(this);
    if (settings.startupMapEnabled()) {
        changeMapStyle(settings.startupMapStyle());
    } else {
        changeMapStyle(Weather::MapStyle::SatelliteMapStyle);
    }
}

void WeatherProvider::resetSource(bool load)
{
    Settings settings(this);
    if (settings.weatherSource() == Sources::Germany) {
        _copyrightLink = std::make_unique<Hyperlink>(
            QStringLiteral("© Deutscher Wetterdienst"),
            QStringLiteral("https://dwd.de"));
    } else {
        _copyrightLink = std::make_unique<Hyperlink>(
            QStringLiteral("© ") + tr("Slovenian Environment Agency"),
            QStringLiteral("https://www.arso.gov.si"));
    }
    emit copyrightChanged();

    _currentType = Weather::UnknownMapType;
    _currentWeather->clear();
    if (load) {
        requestStations();
    }
}

void WeatherProvider::requestCurrentWeatherInfo(const QGeoCoordinate &coordinate)
{
    stopTimerCurrent();

    if (coordinate.isValid()) {
        qDebug() << "Requesting current weather details:" << coordinate;
        APIRequest request = API::stations(coordinate);
        APILoader::request(std::move(request));
    } else if (current()->hasStation()) {
        QString id = current()->station()->forecastOnly() ? current()->station()->currentWeatherSource()->id() : current()->station()->id();
        QStringList alertsAreas;
        alertsAreas.append(current()->station()->alertsArea());
        if (current()->station()->forecastOnly()) {
            alertsAreas.append(current()->station()->currentWeatherSource()->alertsArea());
        }

        qDebug() << "Requesting current weather details:" << id;
        APIRequest requestCurrentWeather = API::stationWeatherCondition(id);
        APILoader::request(std::move(requestCurrentWeather));

        qDebug() << "Requesting current alerts:" << alertsAreas;
        APIRequest requestAlerts = API::alerts(alertsAreas);
        APILoader::request(std::move(requestAlerts));
    }
}

void WeatherProvider::requestStations()
{
    qDebug() << "Requesting stations list";

    APIRequest requestStations = API::stationsList();
    APILoader::request(std::move(requestStations));
}

void WeatherProvider::requestBaseInfo()
{
    qDebug() << "Requesting base weather info";

    APIRequest requestTypes = API::mapTypes();
    APILoader::request(std::move(requestTypes));

    APIRequest requestLegends = API::mapLegends();
    APILoader::request(std::move(requestLegends));
}

void WeatherProvider::requestWeatherMapDetails(const QString &url)
{
    qDebug() << "Requesting weather details:" << url;

    setLoading(true);

    APIRequest request = API::stationsMap(url);
    APILoader::request(std::move(request));
}

void WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

    setLoading(true);

    mapLayers()->setUpdating(true);
    if (_currentType != type) {
        _weatherMapModelBase->clear();
        _weatherMapModel->clear();
        _mapLayersModel->clear();
    }

    APIRequest request = API::mapLayers(type);
    APILoader::request(std::move(request));
}

void WeatherProvider::response(QNetworkReply *reply)
{
    if (!validResponse(reply)) {
        return;
    }

    qDebug() << "Request done:" << reply->url() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    bool valid{};

    // JSON
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (requestFromResponse(reply).call() == QStringLiteral("/maps/types")) {
        const QJsonArray data = document.array();
        _mapInfoModel->clear();
        _mapInfoModel->generateModel(data);

        std::vector<Weather::MapType> types = _mapInfoModel->types();

        Settings settings(this);
        if (settings.startupMapEnabled()
            && std::find(types.begin(), types.end(), settings.startupMapType()) != types.end()) {
            changeMapType(settings.startupMapType());
        } else {
            changeMapType(Weather::MapType::WeatherConditionMap);
        }

        emit currentMapStyleChangedSignal(currentMapStyle());

        removeResponse(reply);
        return;
    }
    if (requestFromResponse(reply).call() == QStringLiteral("/maps/legend")) {
        const QJsonArray data = document.array();

        _mapLegendModel->clear();
        _mapLegendModel->addMapLegends(data);

        removeResponse(reply);
        return;
    }
    if (requestFromResponse(reply).call() == QStringLiteral("/stations/coordinate")) {
        const QJsonArray stations = document.array();
        if (stations.empty()) {
            current()->setStation(nullptr);
            removeResponse(reply);
            return;
        }
        std::unique_ptr<StationInfo> station = StationInfo::fromJson(stations.first().toObject());
        if (station->forecastOnly()) {
            if (stations.size() > 1) {
                station->setCurrentWeatherSource(StationInfo::fromJson(stations[1].toObject()));
            } else {
                // not valid
                current()->setStation(nullptr);
                removeResponse(reply);
                return;
            }
        }
        current()->setStation(std::move(station));
        requestCurrentWeatherInfo(QGeoCoordinate());
        removeResponse(reply);
        return;
    }
    if (requestFromResponse(reply).call() == QStringLiteral("/stations/condition")) {
        const QJsonObject weatherInfo = document.object();
        current()->updateCurrentWeather(WeatherCondition::fromJson(weatherInfo[QStringLiteral("condition")].toObject()));

        _lastUpdateResponseTimeCurrent = QDateTime::currentDateTime();
        startTimerCurrent();
        emit lastUpdateTimeChangedCurrent();
        emit loadingSuccess();

        removeResponse(reply);
        return;
    }
    if (requestFromResponse(reply).call() == QStringLiteral("/alerts/list")) {
        const QJsonArray alertsList = document.array();
        std::vector<std::unique_ptr<WeatherAlert>> alerts;
        alerts.reserve(static_cast<size_t>(alertsList.size()));
        for (const QJsonValue &obj : alertsList) {
            alerts.push_back(WeatherAlert::fromJson(obj.toObject()));
        }
        current()->alerts()->update(alerts);

        removeResponse(reply);
        return;
    }
    if (requestFromResponse(reply).call() == QStringLiteral("/stations/list")) {
        const QJsonArray data = document.array();

        _stationsModel->clear();
        _stationsModel->addStations(data);
        _stationsWithCurrentConditionModel->clear();
        _stationsWithCurrentConditionModel->addEmpty();
        _stationsWithCurrentConditionModel->addStationsWithCurrentCondition(_stationsModel.get());

        emit stationsUpdated();

        removeResponse(reply);

        requestBaseInfo();
        return;
    }

    if (requestFromResponse(reply).call() == QStringLiteral("/stations/map")) {
        _weatherMapModelBase->addEntries(_stationsModel.get(), document.array());
        if (requestFromResponse(reply).url().toString().contains(QStringLiteral("current"))) {
            _weatherMapModel->addEntries(_stationsModel.get(), document.array());
        } else {
            _weatherMapModel->update(_weatherMapModelBase.get(), mapLayers()->timestamp());
        }
        mapLayers()->playResume();
        removeResponse(reply);
        valid = true;
    } else if (requestFromResponse(reply).call() == QStringLiteral("/maps/list")) {
        emit loadingSuccess();

        auto type = Weather::MapType(requestFromResponse(reply).extra().toInt());

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
    emit lastUpdateTimeChanged();
}

void WeatherProvider::error(QNetworkReply *reply,
                            QNetworkReply::NetworkError err)
{
    Q_UNUSED(err)

    if (!validResponse(reply)) {
        return;
    }

    mapLayers()->setUpdating(false, true);
    setLoading(false);

    if (err == QNetworkReply::ContentNotFoundError) {
        if (requestFromResponse(reply).call() == QStringLiteral("/stations/coordinate")
            || requestFromResponse(reply).call() == QStringLiteral("/stations/condition")) {
            current()->setStation(nullptr);
            removeResponse(reply);
            return;
        }
    }

    if (requestFromResponse(reply).call() == QStringLiteral("/stations/condition")) {
        startTimerCurrent();
    } else if (requestFromResponse(reply).call() != QStringLiteral("/maps/types")
               && requestFromResponse(reply).call() != QStringLiteral("/maps/legend")
               && requestFromResponse(reply).call() != QStringLiteral("/stations/coordinate")
               && requestFromResponse(reply).call() != QStringLiteral("/stations/list")) {
        startTimer();
    }

    removeResponse(reply);

    emit loadingError();
}

void WeatherProvider::currentTimeChanged()
{
    if (mapLayers()->renderingType() == Weather::TilesRendering || mapLayers()->renderingType() == Weather::ImageRendering) {
        mapLayers()->playResume();
        return;
    }

    MapLayer *layer = _mapLayersModel->findLayer(Weather::WeatherConditionMap, mapLayers()->timestamp());
    if (layer == nullptr) {
        return;
    }

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
        emit recordEvent(Analytics::MapStyleChanged, Weather::mapStyleToString(style));
    }

    _currentStyle = style;

    emit currentMapStyleChangedSignal(currentMapStyle());
    emit storeState();

    qDebug() << "Map style changed" << style;
}

void WeatherProvider::changeMapType(Weather::MapType type,
                                    bool action)
{
    if (_currentType == type) {
        return;
    }

    if (action) {
        emit recordEvent(Analytics::MapTypeChanged, Weather::mapTypeToString(type));
    }

    _timer->stop();
    requestMapLayers(type);

    _currentType = type;
    _mapLegendProxyModel->setType(_currentType);

    emit currentMapLayerChangedSignal(currentMapLayer());
    emit currentMapLayerHasLegendChangedSignal(currentMapLayerHasLegend());

    emit storeState();
}

void WeatherProvider::currentLocationStatusChanged(bool enabled)
{
    if (!enabled) {
        if (_timerCurrent->isActive()) {
            _timerCurrent->stop();
        }
        current()->setStation(nullptr);
    }
}

void WeatherProvider::currentMapStyleChanged(int index)
{
    changeMapStyle(Weather::MapStyle(index + 1), true);
}

void WeatherProvider::currentMapLayerChanged(int index)
{
    if (index < 0 || index >= _mapInfoModel->rowCount()) {
        return;
    }

    changeMapType(_mapInfoModel->row<MapInfo>(index)->type(), true);
}

int WeatherProvider::currentMapStyle() const
{
    if (_currentStyle == Weather::MapStyle::StreetsLightMapStyle) {
        return 1;
    }
    if (_currentStyle == Weather::MapStyle::StreetsDarkMapStyle) {
        return 2;
    }

    return 0;
}

int WeatherProvider::currentMapLayer() const
{
    std::vector<Weather::MapType> types = _mapInfoModel->types();
    auto it = std::find(types.begin(), types.end(), _currentType);
    return static_cast<int>(std::distance(types.begin(), it));
}

void WeatherProvider::refresh()
{
    _timer->stop();
    _timerCurrent->stop();

    requestMapLayers(_currentType);
    requestCurrentWeatherInfo(QGeoCoordinate());

    emit storeState();
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

    emit storeState();
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
        emit loadingChanged();
    }
}

} // namespace Vremenar

#include "moc_WeatherProvider.cpp"
