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

#include "application/TrayIcon.h"

namespace Vremenar
{

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon(parent)
{
    QIcon icon(QStringLiteral(":/Vremenar/Logo/logo_tray.svg"));
    icon.setIsMask(true);

    setIcon(icon);

    connect(this, &TrayIcon::activated, this, &TrayIcon::activatedCallback);
}

void TrayIcon::activatedCallback(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        emit clicked();
        break;
    default:
        break;
    }
}

} // namespace Vremenar
