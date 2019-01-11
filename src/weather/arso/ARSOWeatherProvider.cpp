/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include "common/NetworkManager.h"
#include "weather/arso/api/ARSOAPIMapLayers.h"
#include "weather/arso/models/ARSOMapLayersModel.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"

#include "weather/arso/ARSOWeatherProvider.h"

namespace Vremenar
{

ARSO::WeatherProvider::WeatherProvider(NetworkManager *network,
                                       QObject *parent)
    : WeatherProviderBase(network, parent),
      _mapLayersModel(std::make_unique<MapLayersModel>(this))
{
    _mapInfoModel->generateModel(supportedMapTypes());
    _mapLayersProxyModel->setSourceModel(_mapLayersModel.get());
}

ARSO::WeatherProvider::~WeatherProvider() = default;

void ARSO::WeatherProvider::requestMapLayers(Weather::MapType type)
{
    qDebug() << "Requesting map type:" << type;

    APIRequest request = ARSO::mapLayers(type);

    _currentReplies.insert(_network->request(request), request);
}

void ARSO::WeatherProvider::response(QNetworkReply *reply)
{
    if (!_currentReplies.contains(reply))
        return;

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (_currentReplies[reply].call() == "/inca_data") {
        auto type = Weather::MapType(_currentReplies[reply].extra().toInt());
        if (_mapLayersModel->rowCount())
            _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(type, document.array());

        removeResponse(reply);
    }
}

} // namespace Vremenar
