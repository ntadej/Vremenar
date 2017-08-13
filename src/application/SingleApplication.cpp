/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "SingleApplication.h"

#ifndef Q_OS_MACOS
#include <QtNetwork/QLocalSocket>

#include "common/Common.h"
#include "common/LocalServer.h"
#endif

SingleApplication::SingleApplication(int &argc,
                                     char **argv)
    : QApplication(argc, argv),
#ifndef Q_OS_MACOS
      _shouldContinue(false) // By default this is not the main process
#else
      _shouldContinue(true) // It is default on OS X
#endif
{
#ifndef Q_OS_MACOS
    QScopedPointer<QLocalSocket> socket(new QLocalSocket(this));

    // Attempt to connect to the LocalServer
    socket->connectToServer(Vremenar::localServer());
    if (socket->waitForConnected(100)) {
        socket->close();
    } else {
        // The attempt was insuccessful, so we continue the program
        _shouldContinue = true;
        _server = new LocalServer(this);
        connect(_server, &LocalServer::connected, this, &SingleApplication::activate);
    }
#endif
}

SingleApplication::~SingleApplication() {}

bool SingleApplication::shouldContinue()
{
    return _shouldContinue;
}
