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

#include <QDebug>

#include "common/NetworkManager.h"
#include "weather/arso/ARSOWeatherProvider.h"
#include "weather/arso/api/ARSOAPIMapLayers.h"
#include "weather/arso/models/ARSOMapLayersModel.h"
#include "weather/common/models/MapLayersProxyModel.h"

ARSOWeatherProvider::ARSOWeatherProvider(Vremenar::NetworkManager *network,
                                         QObject *parent)
    : Vremenar::WeatherProvider(network, parent),
      _mapLayersModel(new ARSOMapLayersModel(this))
{
    _mapLayersProxyModel->setSourceModel(_mapLayersModel);
}

ARSOWeatherProvider::~ARSOWeatherProvider() {}

void ARSOWeatherProvider::requestMapLayers(Vremenar::Weather::MapType type)
{
    Vremenar::APIRequest request = Vremenar::ARSO::mapLayers(type);

    _currentReplies.insert(_network->request(request), request);
}

void ARSOWeatherProvider::response(QNetworkReply *reply)
{
    if (!_currentReplies.contains(reply))
        return;

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (_currentReplies[reply].call() == "/inca_data") {
        Vremenar::Weather::MapType type = Vremenar::Weather::MapType(_currentReplies[reply].extra().toInt());
        if (_mapLayersModel->rowCount())
            _mapLayersModel->clear();
        _mapLayersModel->addMapLayers(type, document.array());

        removeResponse(reply);
    }
}
