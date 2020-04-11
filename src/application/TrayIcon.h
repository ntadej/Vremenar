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

#ifndef VREMENAR_TRAYICON_H_
#define VREMENAR_TRAYICON_H_

#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

class QMenu;

namespace Vremenar
{

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);

public Q_SLOTS:
    void createMenu(const QStringList &maps);
    void setCurrentMap(int index);
    void setCurrentWeather(const QString &location,
                           double temperature,
                           const QString &icon);

Q_SIGNALS:
    void clicked();
    void settings();
    void quit();
    void mapSelected(int index);

private Q_SLOTS:
    void activatedCallback(QSystemTrayIcon::ActivationReason reason);
    void mapSelectedCallback();

private:
    std::unique_ptr<QMenu> _menu{};
    std::unique_ptr<QMenu> _menuDock{};
    std::unique_ptr<QActionGroup> _actionGroup{};
    std::unique_ptr<QAction> _actionShow{};
    std::unique_ptr<QAction> _actionSettings{};
    std::unique_ptr<QAction> _actionQuit{};
};

} // namespace Vremenar

#endif // VREMENAR_TRAYICON_H_
