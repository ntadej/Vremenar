/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "common/NetworkManager.h"

#include "common/api/APIRequestBase.h"

#include <QtCore/QObject>
#include <QtCore/QStandardPaths>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <cstdint>
#include <memory>

namespace
{
constexpr std::uint64_t GB{1073741824};
} // namespace

namespace Vremenar
{

NetworkManager::NetworkManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
    _cache = std::make_unique<QNetworkDiskCache>(this);
    _cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    _cache->setMaximumCacheSize(GB); // 1 GB
    setCache(_cache.get());
}

QNetworkReply *NetworkManager::request(const APIRequestBase &request)
{
    if (!request.silent()) {
        qDebug() << "Requesting:" << request.url();
    }

    QNetworkReply *reply{};
    switch (request.operation()) {
    case QNetworkAccessManager::PostOperation:
        reply = post(request, request.data());
        break;
    case QNetworkAccessManager::GetOperation:
    default:
        reply = get(request);
        break;
    }

    connect(reply, &QNetworkReply::errorOccurred, this, &NetworkManager::httpError);
    connect(reply, &QNetworkReply::finished, this, &NetworkManager::httpRequestFinished);

    return reply;
}

void NetworkManager::httpError(QNetworkReply::NetworkError err)
{
    auto *reply = qobject_cast<QNetworkReply *>(QObject::sender());

    qDebug() << "Network Error:" << err << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << reply->request().url();

    emit error(reply, err);
}

void NetworkManager::httpRequestFinished()
{
    auto *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    emit result(reply);

    disconnect(reply, &QNetworkReply::errorOccurred, this, &NetworkManager::httpError);
    disconnect(reply, &QNetworkReply::finished, this, &NetworkManager::httpRequestFinished);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_NetworkManager.cpp"
// NOLINTEND
