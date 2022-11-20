/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "common/NetworkManager.h"

#include "common/api/APILoader.h"

namespace Vremenar
{

APILoader::APILoader(NetworkManager *network,
                     QObject *parent)
    : QObject(parent),
      _network(network)
{
    connect(_network, &NetworkManager::error, this, &APILoader::error);
    connect(_network, &NetworkManager::result, this, &APILoader::response);
}

void APILoader::request(APIRequestBase request)
{
    _currentReplies.insert(network()->request(request), request);

    _requesting = true;
    emit requestingChanged();
}

const APIRequestBase APILoader::requestFromResponse(QNetworkReply *reply)
{
    return _currentReplies.value(reply);
}

bool APILoader::validResponse(QNetworkReply *reply)
{
    return _currentReplies.contains(reply);
}

void APILoader::removeResponse(QNetworkReply *reply)
{
    if (_currentReplies.contains(reply)) {
        _currentReplies.remove(reply);
        reply->deleteLater();

        if (_currentReplies.empty()) {
            _requesting = false;
            emit requestingChanged();
        }
    }
}

void APILoader::error(QNetworkReply *reply,
                      QNetworkReply::NetworkError err)
{
    Q_UNUSED(err)

    if (_currentReplies.contains(reply)) {
        removeResponse(reply);
    }
}

void APILoader::response(QNetworkReply *reply)
{
    removeResponse(reply);
}

} // namespace Vremenar

#include "moc_APILoader.cpp"
