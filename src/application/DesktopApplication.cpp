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

#include "application/DesktopApplication.h"

#include "application/SingleApplication.h"
#include "common/Output.h"

#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtGui/QFileOpenEvent>

#if defined(Q_OS_WINDOWS)
#include <Windows.h>
#endif

namespace Vremenar
{

DesktopApplication::DesktopApplication(int &argc,
                                       char **argv,
                                       QObject *parent)
    : SingleApplication(argc, argv, parent)
{
    installEventFilter(this);

#if defined(Q_OS_MACOS)
    setupDockHandler();
#elif defined(Q_OS_WINDOWS)
    // restart
    std::wstring args;
    RegisterApplicationRestart(args.data(), 0);
#endif

    Output::welcome();
}

#if !defined(Q_OS_MACOS)
DesktopApplication DesktopApplication::init(int &argc,
                                            char **argv)
{
    return DesktopApplication(argc, argv);
}
#endif

bool DesktopApplication::eventFilter(QObject *object,
                                     QEvent *event)
{
    if (event->type() == QEvent::FileOpen) {
        auto *fileEvent = dynamic_cast<QFileOpenEvent *>(event);
        if (!fileEvent->url().isEmpty()) {
            fileEvent->accept();
            emit urlOpened(fileEvent->url().toString());
        }
    }

    return QObject::eventFilter(object, event);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_DesktopApplication.cpp"
// NOLINTEND
