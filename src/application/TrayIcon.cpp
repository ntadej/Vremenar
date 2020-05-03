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
    : QSystemTrayIcon(parent),
      _menu(std::make_unique<QMenu>()),
      _menuDock(std::make_unique<QMenu>()),
      _actionShow(std::make_unique<QAction>(tr("Show"))),
      _actionSettings(std::make_unique<QAction>(tr("Settings"))),
      _actionQuit(std::make_unique<QAction>(tr("Quit")))
{
    QIcon icon(QStringLiteral(":/Vremenar/Logo/logo_tray.png"));
    icon.setIsMask(true);
    setIcon(icon);

    setContextMenu(_menu.get());
#ifdef Q_OS_MAC
    _menuDock->setAsDockMenu();
#endif

    connect(this, &TrayIcon::activated, this, &TrayIcon::activatedCallback);
    connect(_actionShow.get(), &QAction::triggered, this, &TrayIcon::clicked);
    connect(_actionSettings.get(), &QAction::triggered, this, &TrayIcon::settings);
    connect(_actionQuit.get(), &QAction::triggered, this, &TrayIcon::quit);
}

void TrayIcon::activatedCallback(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        Q_EMIT clicked();
        break;
    default:
        break;
    }
}

void TrayIcon::mapSelectedCallback()
{
    auto *action = qobject_cast<QAction *>(sender());
    if (action == nullptr) {
        return;
    }

    Q_EMIT mapSelected(_actionGroup->actions().indexOf(action));
}

void TrayIcon::createMenu(const QStringList &maps)
{
    _menu->clear();
    _menuDock->clear();
    _actionGroup = std::make_unique<QActionGroup>(_menu.get());
    _actionGroup->setExclusive(true);

    _menu->addAction(_actionShow.get());
    _menu->addSeparator()->setText(tr("Map Type"));

    for (const QString &map : maps) {
        QAction *a = _menu->addAction(map);
        a->setCheckable(true);
        _actionGroup->addAction(a);
        _menuDock->addAction(a);
        connect(a, &QAction::triggered, this, &TrayIcon::mapSelectedCallback);
    }

    _menu->addSeparator();
    _menu->addAction(_actionSettings.get());
    _menu->addAction(_actionQuit.get());
}

void TrayIcon::setCurrentMap(int index)
{
    if (_actionGroup == nullptr || _actionGroup->actions().empty()) {
        return;
    }

    if (index < _actionGroup->actions().size()) {
        _actionGroup->actions().at(index)->setChecked(true);
    }
}

void TrayIcon::setCurrentWeather(const QString &location,
                                 double temperature,
                                 const QString &icon)
{
    if (!location.isEmpty()) {
        setToolTip(QStringLiteral("%1°").arg(temperature));
        QIcon i(QStringLiteral(":/Vremenar/Maps/TrayMask/%1.png").arg(icon));
        i.setIsMask(true);
        setIcon(i);
    } else {
        setToolTip(QString());
        QIcon i(QStringLiteral(":/Vremenar/Logo/logo_tray.png"));
        i.setIsMask(true);
        setIcon(i);
    }
}

} // namespace Vremenar
