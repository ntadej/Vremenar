/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/NetworkManager.h"
#include "weather/common/api/APILoader.h"

APILoader::APILoader(NetworkManager *network,
                     QObject *parent)
    : QObject(parent),
      _network(network)
{
    if (!_network) {
        _network = new NetworkManager(this);
    }

    connect(_network, &NetworkManager::error, this, &APILoader::error);
    connect(_network, &NetworkManager::result, this, &APILoader::response);
}

APILoader::~APILoader() {}

void APILoader::removeResponse(QNetworkReply *reply)
{
    if (_currentReplies.contains(reply)) {
        _currentReplies.remove(reply);
        reply->deleteLater();
    }
}

void APILoader::error(QNetworkReply *reply,
                      QNetworkReply::NetworkError err)
{
    if (_currentReplies.contains(reply)) {
        if (err == QNetworkReply::UnknownServerError) {
            qDebug() << "Retrying:" << _currentReplies[reply].call() << _currentReplies[reply].url();

            _currentReplies.insert(_network->request(_currentReplies[reply]), _currentReplies[reply]);
        }

        _currentReplies.remove(reply);
        reply->deleteLater();
    }
}

void APILoader::response(QNetworkReply *reply)
{
    if (_currentReplies.contains(reply)) {
        _currentReplies.remove(reply);
        reply->deleteLater();
    }
}
