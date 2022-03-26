/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
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

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtGui/QActionGroup>
#else
#include <QtWidgets/QActionGroup>
#endif

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

    void showMapsMenu(QPoint point);
    void showSettingsMenu(QPoint point);

public slots:
    void createMenu(const QStringList &styles,
                    const QStringList &maps);
    void setCurrentStyle(int index);
    void setCurrentMap(int index);
    void setCurrentStation(const Vremenar::StationInfo *station);
    void setCurrentCondition(const Vremenar::WeatherCondition *condition);

signals:
    void triggered();
    void settings();
    void checkForUpdates();
    void about();
    void quit();
    void styleSelected(int index);
    void mapSelected(int index);

private slots:
    void activatedCallback(QSystemTrayIcon::ActivationReason reason);
    void styleSelectedCallback();
    void mapSelectedCallback();

private:
    std::unique_ptr<QMenu> _menu{};
    std::unique_ptr<QMenu> _menuMaps{};
    std::unique_ptr<QMenu> _menuDock{};
    std::unique_ptr<QMenu> _menuSettings{};
    std::unique_ptr<QActionGroup> _actionGroupStyles{};
    std::unique_ptr<QActionGroup> _actionGroupMaps{};
    std::unique_ptr<QAction> _actionShow{};
    std::unique_ptr<QAction> _actionSettings{};
    std::unique_ptr<QAction> _actionCheckForUpdates{};
    std::unique_ptr<QAction> _actionAbout{};
    std::unique_ptr<QAction> _actionQuit{};
};

} // namespace Vremenar

#endif // VREMENAR_TRAYICON_H_
