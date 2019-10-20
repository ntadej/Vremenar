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

#include "application/SingleApplication.h"

#ifndef Q_OS_MACOS
#include <QtNetwork/QLocalSocket>

#include "common/Common.h"
#include "common/LocalServer.h"
#endif

namespace Vremenar
{

SingleApplication::SingleApplication(int &argc,
                                     char **argv,
                                     QObject *parent)
    : QApplication(argc, argv),
#ifndef Q_OS_MACOS
      _shouldContinue(false) // By default this is not the main process
#else
      _shouldContinue(true) // It is default on OS X
#endif
{
    Q_UNUSED(parent)

#ifndef Q_OS_MACOS
    auto socket = std::make_unique<QLocalSocket>(this);

    // Attempt to connect to the LocalServer
    socket->connectToServer(Vremenar::localServer());
    if (socket->waitForConnected(100)) {
        socket->close();
    } else {
        // The attempt was insuccessful, so we continue the program
        _shouldContinue = true;
        _server = std::make_unique<LocalServer>(this);
        connect(_server.get(), &LocalServer::connected, this, &SingleApplication::activate);
    }
#endif
}

} // namespace Vremenar
