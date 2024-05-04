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

#include "common/LocalServer.h"

#include "Config.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QLocalServer>

#include <memory>

namespace Vremenar
{

LocalServer::LocalServer(QObject *parent)
    : QObject(parent)
{
    const QString serverName = QString(Vremenar::name) + "_localserver";

    _server = std::make_unique<QLocalServer>(this);
    _server->removeServer(serverName);
    if (!_server->listen(serverName)) {
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

// NOLINTBEGIN
#include "moc_LocalServer.cpp"
// NOLINTEND
