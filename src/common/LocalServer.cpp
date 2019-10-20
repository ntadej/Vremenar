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

#include <QtCore/QDebug>

#include "common/LocalServer.h"

#include "Config.h"

namespace Vremenar
{

LocalServer::LocalServer(QObject *parent)
    : QObject(parent)
{
    QString name = QString(Vremenar::name) + "_localserver";

    _server = std::make_unique<QLocalServer>(this);
    _server->removeServer(name);
    if (!_server->listen(name)) {
        qCritical() << "Local server could not be started." << _server->errorString();
        return;
    }

    connect(_server.get(), &QLocalServer::newConnection, this, &LocalServer::newConnection);
}

void LocalServer::newConnection()
{
    Q_EMIT connected();
}

} // namespace Vremenar
