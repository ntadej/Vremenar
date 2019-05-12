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

#include <QtCore/QDebug>
#include <QtGui/QWindow>

#include <objc/message.h>
#include <objc/objc.h>

#include <ApplicationServices/ApplicationServices.h>
#include <Cocoa/Cocoa.h>

#include "application/DesktopApplication.h"

namespace Vremenar
{

bool dockClickHandler(id self,
                      SEL cmd,
                      ...)
{
    Q_UNUSED(self)
    Q_UNUSED(cmd)

    static_cast<DesktopApplication *>(qApp)->dockClickedCallback();

    return true;
}

bool DesktopApplication::isDark()
{
    if (@available(macOS 10.14, *)) {
        NSAppearanceName basicAppearance = [[NSAppearance currentAppearance] bestMatchFromAppearancesWithNames:@[
            NSAppearanceNameAqua,
            NSAppearanceNameDarkAqua
        ]];
        return [basicAppearance isEqualToString:NSAppearanceNameDarkAqua];
    } else {
        return NO;
    }
}

void DesktopApplication::setupDockHandler()
{
    Class cls = objc_getClass("NSApplication");
    id appInst = objc_msgSend(cls, sel_registerName("sharedApplication"));

    if (appInst) {
        id delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = objc_msgSend(delegate, sel_registerName("class"));
        SEL shouldHandle = sel_registerName("applicationShouldHandleReopen:hasVisibleWindows:");
        if (class_getInstanceMethod(delClass, shouldHandle)) {
            if (class_replaceMethod(delClass, shouldHandle, reinterpret_cast<IMP>(dockClickHandler), "B@:"))
                qDebug() << "Registered dock click handler (replaced original method)";
            else
                qWarning() << "Failed to replace method for dock click handler";
        } else {
            if (class_addMethod(delClass, shouldHandle, reinterpret_cast<IMP>(dockClickHandler), "B@:"))
                qDebug() << "Registered dock click handler";
            else
                qWarning() << "Failed to register dock click handler";
        }
    }
}

void DesktopApplication::dockSetVisibility(bool visible)
{
    if (visible) {
        dockShow();
    } else {
        dockHide();
    }
}

void DesktopApplication::dockShow()
{
    BOOL active = [[NSRunningApplication currentApplication] isActive];
    ProcessSerialNumber psn = {0, kCurrentProcess};
    if (active) {
        // Workaround buggy behavior of TransformProcessType.
        // http://stackoverflow.com/questions/7596643/
        NSArray *runningApps = [NSRunningApplication
            runningApplicationsWithBundleIdentifier:@"com.apple.dock"];
        for (NSRunningApplication *app in runningApps) {
            [app activateWithOptions:NSApplicationActivateIgnoringOtherApps];
            break;
        }
        dispatch_time_t one_ms = dispatch_time(DISPATCH_TIME_NOW, USEC_PER_SEC);
        dispatch_after(one_ms, dispatch_get_main_queue(), ^{
          TransformProcessType(&psn, kProcessTransformToForegroundApplication);
          dispatch_time_t one_ms = dispatch_time(DISPATCH_TIME_NOW, USEC_PER_SEC);
          dispatch_after(one_ms, dispatch_get_main_queue(), ^{
            [[NSRunningApplication currentApplication]
                activateWithOptions:NSApplicationActivateIgnoringOtherApps];
          });
        });
    } else {
        TransformProcessType(&psn, kProcessTransformToForegroundApplication);
    }
}

void DesktopApplication::dockHide()
{
    QWindowList windows = QGuiApplication::allWindows();

    for (QWindow *window : windows) {
        NSView *nativeView = reinterpret_cast<NSView *>(window->winId());
        NSWindow *nativeWindow = [nativeView window];
        [nativeWindow setCanHide:NO];
    }

    ProcessSerialNumber psn = {0, kCurrentProcess};
    TransformProcessType(&psn, kProcessTransformToUIElementApplication);

    qDebug() << "Dock icon hidden";
}

void DesktopApplication::setupTitleBarLessWindow(WId winId)
{
    if (!winId)
        return;

    NSView *nativeView = reinterpret_cast<NSView *>(winId);
    NSWindow *nativeWindow = [nativeView window];

    [nativeWindow setStyleMask:[nativeWindow styleMask] | NSWindowStyleMaskFullSizeContentView | NSWindowTitleHidden];
    [nativeWindow setTitlebarAppearsTransparent:YES];
}

void DesktopApplication::dockClickedCallback()
{
    emit dockClicked();
}

}
