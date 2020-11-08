/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
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

#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

class QMenu;

namespace Vremenar
{

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);

public Q_SLOTS:
    void createMenu(const QStringList &styles,
                    const QStringList &maps);
    void setCurrentStyle(int index);
    void setCurrentMap(int index);
    void setCurrentWeather(const StationInfo *station,
                           const WeatherCondition *condition);

Q_SIGNALS:
    void triggered();
    void settings();
    void quit();
    void styleSelected(int index);
    void mapSelected(int index);

private Q_SLOTS:
    void activatedCallback(QSystemTrayIcon::ActivationReason reason);
    void styleSelectedCallback();
    void mapSelectedCallback();

private:
    std::unique_ptr<QMenu> _menu{};
    std::unique_ptr<QMenu> _menuDock{};
    std::unique_ptr<QActionGroup> _actionGroupStyles{};
    std::unique_ptr<QActionGroup> _actionGroupMaps{};
    std::unique_ptr<QAction> _actionShow{};
    std::unique_ptr<QAction> _actionSettings{};
    std::unique_ptr<QAction> _actionQuit{};
};

} // namespace Vremenar

#endif // VREMENAR_TRAYICON_H_
