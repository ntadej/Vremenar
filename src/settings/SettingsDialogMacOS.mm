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

#include <Cocoa/Cocoa.h>

#include "settings/Settings.h"

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

namespace Vremenar
{

void SettingsDialog::initializeMacOS()
{
    removeToolBar(ui->toolBar);

    _macToolbar = std::make_unique<QMacToolBar>(this);

    _macItemGeneral = std::unique_ptr<QMacToolBarItem>(_macToolbar->addItem(QIcon(QStringLiteral(":/Vremenar/Icons/32x32/preferences-system.png")), tr("General")));
    _macItemGeneral->setSelectable(true);
    connect(_macItemGeneral.get(), &QMacToolBarItem::activated, this, &SettingsDialog::actionToggled);

    _macItemInterface = std::unique_ptr<QMacToolBarItem>(_macToolbar->addItem(QIcon(QStringLiteral(":/Vremenar/Icons/32x32/preferences-system-windows-actions.png")), tr("Interface")));
    _macItemInterface->setSelectable(true);
    connect(_macItemInterface.get(), &QMacToolBarItem::activated, this, &SettingsDialog::actionToggled);

    window()->winId(); // create window->windowhandle()
    _macToolbar->attachToWindow(this->window()->windowHandle());

    NSToolbar *toolbar = _macToolbar->nativeToolbar();
    NSToolbarItem *toolbarItem = _macItemGeneral->nativeToolBarItem();
    NSString *toolbarItemId = [toolbarItem itemIdentifier];
    [toolbar setSelectedItemIdentifier:toolbarItemId];

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto *view = reinterpret_cast<NSView *>(window()->winId());
    NSWindow *window = [view window];
    if (@available(macOS 11.0, *)) {
        window.toolbarStyle = NSWindowToolbarStylePreference;
    }
    NSRect frame = [window frame];
    double extraHeight = frame.size.height - NSHeight([[window contentView] frame]);
    frame.origin.y += frame.size.height;
    frame.origin.y -= ui->pageGeneral->sizeHint().height() + extraHeight;
    frame.size.height = ui->pageGeneral->sizeHint().height() + extraHeight;
    [window setFrame:frame display:YES];
}

void SettingsDialog::retranslateMacOS()
{
    _macItemGeneral->setText(tr("General"));
    _macItemInterface->setText(tr("Interface"));
}

void SettingsDialog::actionToggledMacOS()
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto *view = reinterpret_cast<NSView *>(window()->winId());
    NSWindow *window = [view window];
    NSRect frame = [window frame];

    double extraHeight = frame.size.height - NSHeight([[window contentView] frame]);
    int stackHeight = 0;
    auto *item = qobject_cast<QMacToolBarItem *>(sender());
    ui->stackedWidget->hide();
    if (item == _macItemGeneral.get()) {
        ui->stackedWidget->setCurrentWidget(ui->pageGeneral);
        stackHeight = ui->pageGeneral->sizeHint().height();
    } else if (item == _macItemInterface.get()) {
        ui->stackedWidget->setCurrentWidget(ui->pageInterface);
        stackHeight = ui->pageInterface->sizeHint().height();
    }

    frame.origin.y += frame.size.height;
    frame.origin.y -= stackHeight + extraHeight;
    frame.size.height = stackHeight + extraHeight;

    [window setFrame:frame display:YES animate:YES];

    setWindowTitle(item->text());
    ui->stackedWidget->show();
}

} // namespace Vremenar
