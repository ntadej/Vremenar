/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
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
#include "weather/arso/api/ARSOAPIMapLayers.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/models/MapLegendProxyModel.h"

#include "weather/arso/ARSOWeatherProvider.h"

namespace
{
constexpr double ARSODefaultTopLeftLatitude{12.1};
constexpr double ARSODefaultTopLeftLongitude{47.42};
constexpr double ARSODefaultBottomRightLatitude{17.44};
constexpr double ARSODefaultBottomRightLongitude{44.67};
} // namespace

namespace Vremenar
{

ARSO::WeatherProvider::WeatherProvider(NetworkManager *network,
                                       QObject *parent)
    : WeatherProviderBase(network, defaultMapCoordinates(), parent),
      _forecastModel(std::make_unique<ForecastModel>(this)),
      _mapLayersModel(std::make_unique<MapLayersModel>(this)),
      _mapLegendModel(std::make_unique<MapLegendModel>(this))
{
    forecast()->setSourceModel(_forecastModel.get());
    mapInfo()->generateModel(supportedMapTypes());
    mapLayers()->setSourceModel(_mapLayersModel.get());
    mapLegend()->setSourceModel(_mapLegendModel.get());

    _copyrightLink = std::make_unique<Hyperlink>(
        QStringLiteral("© ") + tr("Slovenian Environment Agency"),
        QStringLiteral("https://www.arso.gov.si"));
}

void ARSO::WeatherProvider::requestForecastDetails(int index)
{
    qDebug() << "Requesting forecast details:" << index;

    APIRequest request = ARSO::mapForecastDetails(mapLayers()->data(mapLayers()->index(0, 0), MapLayer::UrlRole).toString());
    currentReplies()->insert(network()->request(request), request);
}

void ARSO::WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

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
    if (currentReplies()->value(reply).call() == QStringLiteral("/forecast_data")) {
        _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(Weather::ForecastMap, document.array());

        removeResponse(reply);
        requestForecastDetails(0);

        return;
    }

    if (currentReplies()->value(reply).call() == QStringLiteral("/forecast_data_details")) {
        _forecastModel->clear();
        _forecastModel->addEntries(document.object()[QStringLiteral("features")].toArray());

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
    startTimer();
    Q_EMIT lastUpdateTimeChanged();
}

QVariant ARSO::WeatherProvider::defaultMapCoordinates() const
{
    return MapLayer::geoRectangleToList(QGeoRectangle(
        QGeoCoordinate(ARSODefaultTopLeftLatitude, ARSODefaultTopLeftLongitude),
        QGeoCoordinate(ARSODefaultBottomRightLatitude, ARSODefaultBottomRightLongitude)));
}

} // namespace Vremenar
