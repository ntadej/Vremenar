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

#include "weather/arso/ARSOWeatherProvider.h"

namespace Vremenar
{

ARSO::WeatherProvider::WeatherProvider(NetworkManager *network,
                                       QObject *parent)
    : WeatherProviderBase(network, defaultMapCoordinates(), parent),
      _mapLayersModel(std::make_unique<MapLayersModel>(this))
{
    _mapInfoModel->generateModel(supportedMapTypes());
    _mapLayersProxyModel->setSourceModel(_mapLayersModel.get());

    _copyrightLink = std::make_unique<Hyperlink>(
        QStringLiteral("© ") + tr("Slovenian Environment Agency"),
        QStringLiteral("https://www.arso.gov.si"));
}

void ARSO::WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

    APIRequest request = ARSO::mapLayers(type);

    _currentReplies.insert(_network->request(request), request);
}

void ARSO::WeatherProvider::response(QNetworkReply *reply)
{
    if (!_currentReplies.contains(reply)) {
        return;
    }

    bool valid{};

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (_currentReplies[reply].call() == QStringLiteral("/inca_data")) {
        auto type = Weather::MapType(_currentReplies.value(reply).extra().toInt());
        if (_mapLayersModel->rowCount() != 0) {
            _mapLayersModel->clear();
        }
        _mapLayersModel->addMapLayers(type, document.array());

        removeResponse(reply);

        valid = true;
    }

    if (!valid) {
        return;
    }

    _lastUpdateResponseTime = QDateTime::currentDateTime();
    startTimer();
    emit lastUpdateTimeChanged();
}

QVariant ARSO::WeatherProvider::defaultMapCoordinates() const
{
    return MapLayer::geoRectangleToList(QGeoRectangle(QGeoCoordinate(12.1, 47.42), QGeoCoordinate(17.44, 44.67)));
}

} // namespace Vremenar
