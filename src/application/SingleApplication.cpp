/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "application/SingleApplication.h"

#ifndef Q_OS_MACOS
#include <QtNetwork/QLocalSocket>

#include "Config.h"
#endif

namespace Vremenar
{

SingleApplication::SingleApplication(int &argc,
                                     char **argv,
                                     QObject *parent)
    : QApplication(argc, argv)
{
    Q_UNUSED(parent)

#ifndef Q_OS_MACOS
    _server = std::make_unique<LocalServer>(this);
    connect(_server.get(), &LocalServer::connected, this, &SingleApplication::activate);
#endif
}

bool SingleApplication::shouldContinue()
{
#ifndef Q_OS_MACOS
    auto socket = std::make_unique<QLocalSocket>();

    // Attempt to connect to the LocalServer
    socket->connectToServer(QString(Vremenar::name) + "_localserver");
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    if (socket->waitForConnected(100)) {
        socket->close();
        return false;
    }
#endif
    return true;
}

} // namespace Vremenar

#include "moc_SingleApplication.cpp"
