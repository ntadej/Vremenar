/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_TRAYICON_H_
#define VREMENAR_TRAYICON_H_

#include <QtWidgets/QSystemTrayIcon>

namespace Vremenar
{

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);

signals:
    void clicked();

private slots:
    void activatedCallback(QSystemTrayIcon::ActivationReason reason);
};

} // namespace Vremenar

#endif // VREMENAR_TRAYICON_H_
