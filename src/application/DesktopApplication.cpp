/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtGui/QFileOpenEvent>

#include "common/Output.h"

#include "application/DesktopApplication.h"

namespace Vremenar
{

DesktopApplication::DesktopApplication(int &argc,
                                       char **argv)
    : SingleApplication(argc, argv)
{
    installEventFilter(this);

#ifdef Q_OS_MACOS
    setupDockHandler();
#endif
}

void DesktopApplication::postInit()
{
    Vremenar::Output::welcome();
}

bool DesktopApplication::eventFilter(QObject *object,
                                     QEvent *event)
{
    if (event->type() == QEvent::FileOpen) {
        auto *fileEvent = dynamic_cast<QFileOpenEvent *>(event);
        if (!fileEvent->url().isEmpty()) {
            emit urlOpened(fileEvent->url().toString());
            return false;
        } else {
            return QObject::eventFilter(object, event);
        }
    } else {
        return QObject::eventFilter(object, event);
    }
}

} // namespace Vremenar
