/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "application/TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon(parent)
{
    QIcon icon(":/Vremenar/Logo/logo_tray.svg");
    icon.setIsMask(true);

    setIcon(icon);
}

TrayIcon::~TrayIcon() {}
