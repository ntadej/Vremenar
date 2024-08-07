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

#include "application/TrayIcon.h"

#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtGui/QIcon>
#include <QtWidgets/QMenu>
#include <QtWidgets/QSystemTrayIcon>

#include <memory>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

TrayIcon::TrayIcon(QObject *parent)
    : QSystemTrayIcon(parent),
      _menu(std::make_unique<QMenu>()),
      _menuMaps(std::make_unique<QMenu>()),
      _menuDock(std::make_unique<QMenu>()),
      _menuSettings(std::make_unique<QMenu>()),
      _actionShow(std::make_unique<QAction>(tr("Show Vremenar"))),
#ifdef Q_OS_MAC
      _actionSettings(std::make_unique<QAction>(tr("Preferences"))),
#else
      _actionSettings(std::make_unique<QAction>(tr("Settings"))),
#endif
      _actionCheckForUpdates(std::make_unique<QAction>(tr("Check for updates"))),
      _actionAbout(std::make_unique<QAction>(tr("About Vremenar"))),
#ifdef Q_OS_MAC
      _actionQuit(std::make_unique<QAction>(tr("Quit Vremenar")))
#else
      _actionQuit(std::make_unique<QAction>(tr("Exit Vremenar")))
#endif
{
    setCurrentCondition(nullptr);

    setContextMenu(_menu.get());
#ifdef Q_OS_MAC
    _menuDock->setAsDockMenu();
#endif

    _menuSettings->addAction(_actionSettings.get());
#ifndef VREMENAR_STORE
    _menuSettings->addAction(_actionCheckForUpdates.get());
#endif
    _menuSettings->addAction(_actionAbout.get());

    connect(this, &TrayIcon::activated, this, &TrayIcon::activatedCallback);
    connect(_actionShow.get(), &QAction::triggered, this, &TrayIcon::triggered);
    connect(_actionSettings.get(), &QAction::triggered, this, &TrayIcon::settings);
    connect(_actionCheckForUpdates.get(), &QAction::triggered, this, &TrayIcon::checkForUpdates);
    connect(_actionAbout.get(), &QAction::triggered, this, &TrayIcon::about);
    connect(_actionQuit.get(), &QAction::triggered, this, &TrayIcon::quit);
}

TrayIcon::~TrayIcon() = default;

void TrayIcon::activatedCallback(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        emit triggered();
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

    emit styleSelected(_actionGroupStyles->actions().indexOf(action));
}

void TrayIcon::mapSelectedCallback()
{
    auto *action = qobject_cast<QAction *>(sender());
    if (action == nullptr) {
        return;
    }

    emit mapSelected(_actionGroupMaps->actions().indexOf(action));
}

void TrayIcon::createMenu(const QStringList &styles,
                          const QStringList &maps)
{
    _menu->clear();
    _menuMaps->clear();
    _menuDock->clear();

    _actionGroupStyles = std::make_unique<QActionGroup>(_menu.get());
    _actionGroupStyles->setExclusive(true);
    _actionGroupMaps = std::make_unique<QActionGroup>(_menu.get());
    _actionGroupMaps->setExclusive(true);

    _menu->addAction(_actionShow.get());

    _menu->addSeparator()->setText(tr("Map Type"));
    _menuMaps->addSeparator()->setText(tr("Map Type"));
    for (const QString &map : maps) {
        QAction *a = _menu->addAction(map);
        a->setCheckable(true);
        _actionGroupMaps->addAction(a);
        _menuMaps->addAction(a);
        _menuDock->addAction(a);
        connect(a, &QAction::triggered, this, &TrayIcon::mapSelectedCallback);
    }

    _menu->addSeparator()->setText(tr("Map Style"));
    _menuMaps->addSeparator()->setText(tr("Map Style"));
    for (const QString &style : styles) {
        QAction *a = _menu->addAction(style);
        a->setCheckable(true);
        _actionGroupStyles->addAction(a);
        _menuMaps->addAction(a);
        connect(a, &QAction::triggered, this, &TrayIcon::styleSelectedCallback);
    }

    _menu->addSeparator();
    _menu->addAction(_actionSettings.get());
    _menu->addAction(_actionQuit.get());
}

void TrayIcon::setCurrentStyle(qsizetype index)
{
    if (_actionGroupStyles == nullptr || _actionGroupStyles->actions().empty()) {
        return;
    }

    if (index >= 0 && index < _actionGroupStyles->actions().size()) {
        _actionGroupStyles->actions().at(index)->setChecked(true);
    }
}

void TrayIcon::setCurrentMap(qsizetype index)
{
    if (_actionGroupMaps == nullptr || _actionGroupMaps->actions().empty()) {
        return;
    }

    if (index >= 0 && index < _actionGroupMaps->actions().size()) {
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
        QIcon i(u":/Vremenar/Weather/TrayMask/%1.png"_s.arg(condition->icon()));
        i.setIsMask(true);
#else
        QIcon i;
        i.addFile(u":/Vremenar/Weather/Tray/16/%1.png"_s.arg(condition->icon()), QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(u":/Vremenar/Weather/Tray/24/%1.png"_s.arg(condition->icon()), QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(u":/Vremenar/Weather/Tray/32/%1.png"_s.arg(condition->icon()), QSize(32, 32)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
        setIcon(i);
    } else {
        setToolTip(QString());
#ifdef Q_OS_MACOS
        QIcon i(u":/Vremenar/Logo/logo_tray.png"_s);
        i.setIsMask(true);
#else
        QIcon i;
        i.addFile(u":/Vremenar/Logo/16x16/vremenar.png"_s, QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(u":/Vremenar/Logo/24x24/vremenar.png"_s, QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        i.addFile(u":/Vremenar/Logo/32x32/vremenar.png"_s, QSize(32, 32)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
        setIcon(i);
    }
}

void TrayIcon::showMapsMenu(QPoint point)
{
    _menuMaps->popup(point);
}

void TrayIcon::showSettingsMenu(QPoint point)
{
    _menuSettings->popup(point);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_TrayIcon.cpp"
// NOLINTEND
