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

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include "common/NetworkManager.h"
#include "weather/arso/ARSOCurrentWeather.h"
#include "weather/arso/api/ARSOAPILocations.h"
#include "weather/arso/api/ARSOAPIMapLayers.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/models/MapLegendProxyModel.h"

#include "weather/arso/ARSOWeatherProvider.h"

namespace Vremenar
{

ARSO::WeatherProvider::WeatherProvider(NetworkManager *network,
                                       QObject *parent)
    : WeatherProviderBase(network, parent),
      _forecastModel(std::make_unique<ForecastModel>(this)),
      _mapLayersModel(std::make_unique<MapLayersModel>(this)),
      _mapLegendModel(std::make_unique<MapLegendModel>(this))
{
    setupCurrentWeather(std::make_unique<CurrentWeather>(this));
    forecast()->setSourceModel(_forecastModel.get());
    mapInfo()->generateModel(supportedMapTypes());
    mapLayers()->setDefaultCoordinates(MapLayer::geoRectangleToList(defaultMapCoordinates()));
    mapLayers()->setSourceModel(_mapLayersModel.get());
    mapLegend()->setSourceModel(_mapLegendModel.get());

    _copyrightLink = std::make_unique<Hyperlink>(
        QStringLiteral("© ") + tr("Slovenian Environment Agency"),
        QStringLiteral("https://www.arso.gov.si"));

    connect(mapLayers(), &MapLayersProxyModel::timestampChanged, this, &ARSO::WeatherProvider::currentTimeChanged);
}

bool ARSO::WeatherProvider::currentMapLayerHasLegend() const
{
    return !(currentType() == Weather::ForecastMap || currentType() == Weather::CloudCoverageMap);
}

void ARSO::WeatherProvider::requestCurrentWeatherInfo(const QGeoCoordinate &coordinate)
{
    stopTimerCurrent();

    if (coordinate.isValid()) {
        qDebug() << "Requesting current weather details:" << coordinate;
        APIRequest request = ARSO::locations(coordinate);
        currentReplies()->insert(network()->request(request), request);
    } else if (!current()->location().isEmpty()) {
        qDebug() << "Requesting current weather details:" << current()->location();
        APIRequest request = ARSO::locations(current()->location());
        currentReplies()->insert(network()->request(request), request);
    }
}

void ARSO::WeatherProvider::requestForecastDetails(const QString &url)
{
    qDebug() << "Requesting forecast details:" << url;

    setLoading(true);

    APIRequest request = ARSO::mapForecastDetails(url);
    currentReplies()->insert(network()->request(request), request);
}

void ARSO::WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

    setLoading(true);

    _forecastModel->clear();
    _mapLayersModel->clear();

    if (type == Weather::ForecastMap) {
        APIRequest request = ARSO::mapForecast();
        currentReplies()->insert(network()->request(request), request);
    } else {
        APIRequest request = ARSO::mapLayers(type);
        currentReplies()->insert(network()->request(request), request);
    }
}

void ARSO::WeatherProvider::response(QNetworkReply *reply)
{
    if (!currentReplies()->contains(reply)) {
        return;
    }

    bool valid{};

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (currentReplies()->value(reply).call() == QStringLiteral("/locations/coordinate")) {
        QJsonObject properties = document.object()[QStringLiteral("properties")].toObject();
        QString title = properties[QStringLiteral("title")].toString();
        current()->setLocation(title);
        requestCurrentWeatherInfo(QGeoCoordinate());
        removeResponse(reply);
        return;
    }
    if (currentReplies()->value(reply).call() == QStringLiteral("/locations/string")) {
        current()->updateCurrentWeather(document.object());

        setLastUpdatedTimeCurrent(QDateTime::currentDateTime());
        startTimerCurrent();
        Q_EMIT lastUpdateTimeChangedCurrent();

        removeResponse(reply);
        return;
    }

    if (currentReplies()->value(reply).call() == QStringLiteral("/forecast_data")) {
        _forecastModel->clear();
        _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(Weather::ForecastMap, document.array());

        removeResponse(reply);
        return;
    }

    if (currentReplies()->value(reply).call() == QStringLiteral("/forecast_data_details")) {
        _forecastModel->addEntries(document.object()[QStringLiteral("features")].toArray());
        mapLayers()->playResume();
        removeResponse(reply);
        valid = true;
    } else if (currentReplies()->value(reply).call() == QStringLiteral("/inca_data")) {
        auto type = Weather::MapType(currentReplies()->value(reply).extra().toInt());
        _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(type, document.array());

        removeResponse(reply);
        valid = true;
    }

    if (!valid) {
        return;
    }

    setLastUpdatedTime(QDateTime::currentDateTime());
    setLoading(false);
    startTimer();
    Q_EMIT lastUpdateTimeChanged();
}

void ARSO::WeatherProvider::currentTimeChanged()
{
    if (currentType() != Weather::ForecastMap) {
        return;
    }

    MapLayer *layer = _mapLayersModel->findLayer(Weather::ForecastMap, mapLayers()->timestamp());
    if (layer == nullptr) {
        return;
    }

    if (!layer->loaded()) {
        requestForecastDetails(layer->url().toString());
        layer->setLoaded();
    } else {
        mapLayers()->playResume();
    }

    forecast()->setTime(mapLayers()->timestamp());
}

} // namespace Vremenar
