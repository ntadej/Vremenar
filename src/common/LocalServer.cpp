/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>

#include "common/Common.h"

#include "common/LocalServer.h"

namespace Vremenar
{

LocalServer::LocalServer(QObject *parent)
    : QObject(parent)
{
    _server = std::make_unique<QLocalServer>(this);
    _server->removeServer(localServer());
    if (!_server->listen(localServer())) {
        qCritical() << "Local server could not be started." << _server->errorString();
        return;
    }

    connect(_server.get(), &QLocalServer::newConnection, this, &LocalServer::newConnection);
}

void LocalServer::newConnection()
{
    emit connected();
}

} // namespace Vremenar
