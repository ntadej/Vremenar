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
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtGui/QImage>

#include "common/NetworkManager.h"
#include "weather/backend/CurrentWeather.h"
#include "weather/backend/api/APILocations.h"
#include "weather/backend/api/APIMapLayers.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/models/MapLegendProxyModel.h"

#include "weather/backend/WeatherProvider.h"

namespace Vremenar
{

Backend::WeatherProvider::WeatherProvider(NetworkManager *network,
                                          QObject *parent)
    : WeatherProviderBase(network, parent),
      _forecastModelBase(std::make_unique<ForecastModel>(this)),
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

    connect(mapLayers(), &MapLayersProxyModel::timestampChanged, this, &Backend::WeatherProvider::currentTimeChanged);
}

bool Backend::WeatherProvider::currentMapLayerHasLegend() const
{
    return !(currentType() == Weather::ForecastMap || currentType() == Weather::CloudCoverageMap);
}

void Backend::WeatherProvider::requestCurrentWeatherInfo(const QGeoCoordinate &coordinate)
{
    stopTimerCurrent();

    if (coordinate.isValid()) {
        qDebug() << "Requesting current weather details:" << coordinate;
        APIRequest request = Backend::locations(coordinate);
        currentReplies()->insert(network()->request(request), request);
    } else if (!current()->location().isEmpty()) {
        qDebug() << "Requesting current weather details:" << current()->location();
        APIRequest request = Backend::locations(current()->location());
        currentReplies()->insert(network()->request(request), request);
    }
}

void Backend::WeatherProvider::requestForecastDetails(const QString &url)
{
    qDebug() << "Requesting forecast details:" << url;

    setLoading(true);

    APIRequest request = Backend::mapForecastDetails(url);
    currentReplies()->insert(network()->request(request), request);
}

void Backend::WeatherProvider::requestImage(const QString &url)
{
    qDebug() << "Requesting image:" << url;

    setLoading(true);

    APIRequest request = Backend::mapImage(url);
    currentReplies()->insert(network()->request(request), request);
}

void Backend::WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

    setLoading(true);

    mapLayers()->setUpdating(true);
    _forecastModelBase->clear();
    _forecastModel->clear();
    _mapLayersModel->clear();

    if (type == Weather::ForecastMap) {
        APIRequest request = Backend::mapForecast();
        currentReplies()->insert(network()->request(request), request);
    } else {
        APIRequest request = Backend::mapLayers(type);
        currentReplies()->insert(network()->request(request), request);
    }
}

void Backend::WeatherProvider::response(QNetworkReply *reply)
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

    if (currentReplies()->value(reply).call() == QStringLiteral("/forecast_data_details")) {
        _forecastModelBase->addEntries(document.object()[QStringLiteral("features")].toArray());
        if (currentReplies()->value(reply).url().toString().contains(QStringLiteral("latest"))) {
            _forecastModel->addEntries(document.object()[QStringLiteral("features")].toArray());
        } else {
            _forecastModel->update(_forecastModelBase.get(), mapLayers()->timestamp());
        }
        mapLayers()->playResume();
        removeResponse(reply);
        valid = true;
    } else if (currentReplies()->value(reply).call() == QStringLiteral("/maps")) {
        auto type = Weather::MapType(currentReplies()->value(reply).extra().toInt());

        removeResponse(reply);

        mapLayers()->setUpdating(true);

        const QJsonObject data = document.object();

        auto reportedType = Weather::mapTypeFromString(data[QStringLiteral("map_type")].toString());
        if (reportedType == Weather::UnknownMap || reportedType != type) {
            qDebug() << "Invalid map type " << reportedType << ", expected " << type;
            return;
        }

        _forecastModelBase->clear();
        _forecastModel->clear();
        _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(type, data);

        if (type == Weather::ForecastMap) {
            currentTimeChanged();
            return;
        }

        valid = true;
    }

    if (!valid) {
        return;
    }

    mapLayers()->setUpdating(false);

    setLastUpdatedTime(QDateTime::currentDateTime());
    setLoading(false);
    startTimer();
    Q_EMIT lastUpdateTimeChanged();
}

void Backend::WeatherProvider::currentTimeChanged()
{
    if (currentType() != Weather::ForecastMap) {
        requestImage(mapLayers()->url());
        return;
    }

    MapLayer *layer = _mapLayersModel->findLayer(Weather::ForecastMap, mapLayers()->timestamp());
    if (layer == nullptr) {
        return;
    }

    mapLayers()->setImage(QStringLiteral("data:image/jpeg;base64,") + Weather::blankPng);

    if (!layer->loaded()) {
        requestForecastDetails(layer->url().toString());
        layer->setLoaded();
    } else {
        _forecastModel->update(_forecastModelBase.get(), mapLayers()->timestamp());
        mapLayers()->playResume();
    }
}

} // namespace Vremenar
