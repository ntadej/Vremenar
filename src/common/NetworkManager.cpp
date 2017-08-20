/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QStandardPaths>

#include "common/NetworkManager.h"
#include "settings/Settings.h"

NetworkManager::NetworkManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
    _cache = new QNetworkDiskCache(this);
    _cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    _cache->setMaximumCacheSize(1073741824); // 1 GB
    setCache(_cache);
}

NetworkManager::~NetworkManager()
{
    delete _cache;
}

QNetworkReply *NetworkManager::request(APIRequest &request)
{
    qDebug() << "Requesting:" << request.url();

    QNetworkReply *reply;
    switch (request.operation()) {
    case QNetworkAccessManager::PostOperation:
        reply = post(request, request.data());
        break;
    case QNetworkAccessManager::GetOperation:
    default:
        reply = get(request);
        break;
    }

    connect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error), this, &NetworkManager::httpError);
    connect(reply, &QNetworkReply::finished, this, &NetworkManager::httpRequestFinished);

    return reply;
}

void NetworkManager::httpError(QNetworkReply::NetworkError err)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());

    qDebug() << "Network Error:" << err << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << reply->request().url();

    emit error(reply, err);
}

void NetworkManager::httpRequestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    if (reply->error()) {
        return;
    } else {
        emit result(reply);
    }

    disconnect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error), this, &NetworkManager::httpError);
    disconnect(reply, &QNetworkReply::finished, this, &NetworkManager::httpRequestFinished);
}
