/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_TRAYICON_H_
#define VREMENAR_TRAYICON_H_

#include <QtWidgets/QSystemTrayIcon>

class TrayIcon : public QSystemTrayIcon
{
public:
    explicit TrayIcon(QObject *parent = 0);
    virtual ~TrayIcon();
};

#endif // VREMENAR_TRAYICON_H_
