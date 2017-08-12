/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <Cocoa/Cocoa.h>

#include "common/LocaleManager.h"
#include "settings/Settings.h"

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

void SettingsDialog::initializeMacOS()
{
    removeToolBar(ui->toolBar);

    _macToolbar = new QMacToolBar(this);

    _macItemGeneral = _macToolbar->addItem(QIcon(QStringLiteral(":/Vremenar/Icons/32x32/preferences-system.png")), tr("General"));
    _macItemGeneral->setSelectable(true);
    connect(_macItemGeneral, &QMacToolBarItem::activated, this, &SettingsDialog::actionToggled);

    _macItemInterface = _macToolbar->addItem(QIcon(QStringLiteral(":/Vremenar/Icons/32x32/preferences-system-windows-actions.png")), tr("Interface"));
    _macItemInterface->setSelectable(true);
    connect(_macItemInterface, &QMacToolBarItem::activated, this, &SettingsDialog::actionToggled);

    window()->winId(); // create window->windowhandle()
    _macToolbar->attachToWindow(this->window()->windowHandle());

    NSToolbar *toolbar = _macToolbar->nativeToolbar();
    NSToolbarItem *toolbarItem = _macItemGeneral->nativeToolBarItem();
    NSString *toolbarItemId = [toolbarItem itemIdentifier];
    [toolbar setSelectedItemIdentifier:toolbarItemId];

    NSView *view = (NSView *)window()->winId();
    NSWindow *window = [view window];
    NSRect frame = [window frame];
    int extraHeight = frame.size.height - NSHeight([[window contentView] frame]);
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
    NSView *view = (NSView *)window()->winId();
    NSWindow *window = [view window];
    NSRect frame = [window frame];

    int extraHeight = frame.size.height - NSHeight([[window contentView] frame]);
    int stackHeight = 0;
    QMacToolBarItem *item = qobject_cast<QMacToolBarItem *>(sender());
    ui->stackedWidget->hide();
    if (item == _macItemGeneral) {
        ui->stackedWidget->setCurrentWidget(ui->pageGeneral);
        stackHeight = ui->pageGeneral->sizeHint().height();
    } else if (item == _macItemInterface) {
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
