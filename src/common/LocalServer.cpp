/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>

#include "common/Common.h"
#include "common/LocalServer.h"

LocalServer::LocalServer(QObject *parent)
    : QObject(parent)
{
    _server = new QLocalServer(this);
    _server->removeServer(Vremenar::localServer());
    if (!_server->listen(Vremenar::localServer())) {
        qCritical() << "Local server could not be started." << _server->errorString();
        return;
    }

    connect(_server, &QLocalServer::newConnection, this, &LocalServer::newConnection);
}

LocalServer::~LocalServer() {}

void LocalServer::newConnection()
{
    emit connected();
}
