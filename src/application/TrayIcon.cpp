/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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
    : QSystemTrayIcon(parent),
      _menu(std::make_unique<QMenu>()),
      _menuDock(std::make_unique<QMenu>()),
      _actionShow(std::make_unique<QAction>(tr("Show"))),
      _actionSettings(std::make_unique<QAction>(tr("Settings"))),
      _actionQuit(std::make_unique<QAction>(tr("Quit")))
{
    setCurrentCondition(nullptr);

    setContextMenu(_menu.get());
#ifdef Q_OS_MAC
    _menuDock->setAsDockMenu();
#endif

    connect(this, &TrayIcon::activated, this, &TrayIcon::activatedCallback);
    connect(_actionShow.get(), &QAction::triggered, this, &TrayIcon::triggered);
    connect(_actionSettings.get(), &QAction::triggered, this, &TrayIcon::settings);
    connect(_actionQuit.get(), &QAction::triggered, this, &TrayIcon::quit);
}

void TrayIcon::activatedCallback(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        Q_EMIT triggered();
        break;
    default:
        break;
    }
}

void TrayIcon::styleSelectedCallback()
{
    auto *action = qobject_cast<QAction *>(sender());
    if (action == nullptr) {
        return;
    }

    Q_EMIT styleSelected(_actionGroupStyles->actions().indexOf(action));
}

void TrayIcon::mapSelectedCallback()
{
    auto *action = qobject_cast<QAction *>(sender());
    if (action == nullptr) {
        return;
    }

    Q_EMIT mapSelected(_actionGroupMaps->actions().indexOf(action));
}

void TrayIcon::createMenu(const QStringList &styles,
                          const QStringList &maps)
{
    _menu->clear();
    _menuDock->clear();

    _actionGroupStyles = std::make_unique<QActionGroup>(_menu.get());
    _actionGroupStyles->setExclusive(true);
    _actionGroupMaps = std::make_unique<QActionGroup>(_menu.get());
    _actionGroupMaps->setExclusive(true);

    _menu->addAction(_actionShow.get());

    _menu->addSeparator()->setText(tr("Map Style"));
    for (const QString &style : styles) {
        QAction *a = _menu->addAction(style);
        a->setCheckable(true);
        _actionGroupStyles->addAction(a);
        connect(a, &QAction::triggered, this, &TrayIcon::styleSelectedCallback);
    }

    _menu->addSeparator()->setText(tr("Map Type"));
    for (const QString &map : maps) {
        QAction *a = _menu->addAction(map);
        a->setCheckable(true);
        _actionGroupMaps->addAction(a);
        _menuDock->addAction(a);
        connect(a, &QAction::triggered, this, &TrayIcon::mapSelectedCallback);
    }

    _menu->addSeparator();
    _menu->addAction(_actionSettings.get());
    _menu->addAction(_actionQuit.get());
}

void TrayIcon::setCurrentStyle(int index)
{
    if (_actionGroupStyles == nullptr || _actionGroupStyles->actions().empty()) {
        return;
    }

    if (index < _actionGroupStyles->actions().size()) {
        _actionGroupStyles->actions().at(index)->setChecked(true);
    }
}

void TrayIcon::setCurrentMap(int index)
{
    if (_actionGroupMaps == nullptr || _actionGroupMaps->actions().empty()) {
        return;
    }

    if (index < _actionGroupMaps->actions().size()) {
        _actionGroupMaps->actions().at(index)->setChecked(true);
    }
}

void TrayIcon::setCurrentStation(const StationInfo *station)
{
    Q_UNUSED(station)
}

void TrayIcon::setCurrentCondition(const WeatherCondition *condition)
{
    if (condition != nullptr) {
        setToolTip(condition->displayTemperatureShort());
#ifdef Q_OS_MACOS
        QIcon i(QStringLiteral(":/Vremenar/Weather/TrayMask/%1.png").arg(condition->icon()));
        i.setIsMask(true);
#else
        QIcon i;
        i.addFile(QStringLiteral(":/Vremenar/Weather/Tray/16/%1.png").arg(condition->icon()), QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(QStringLiteral(":/Vremenar/Weather/Tray/24/%1.png").arg(condition->icon()), QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(QStringLiteral(":/Vremenar/Weather/Tray/32/%1.png").arg(condition->icon()), QSize(32, 32)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
        setIcon(i);
    } else {
        setToolTip(QString());
#ifdef Q_OS_MACOS
        QIcon i(QStringLiteral(":/Vremenar/Logo/logo_tray.png"));
        i.setIsMask(true);
#else
        QIcon i;
        i.addFile(":/Vremenar/Logo/logo/16x16/vremenar.png", QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(":/Vremenar/Logo/logo/24x24/vremenar.png", QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(":/Vremenar/Logo/logo/32x32/vremenar.png", QSize(32, 32)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
        setIcon(i);
    }
}

} // namespace Vremenar
