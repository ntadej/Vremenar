/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtGui/QWindow>

#include <ApplicationServices/ApplicationServices.h>
#include <Cocoa/Cocoa.h>

#include "DesktopApplication.h"

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

    // Disabled due to resizing repaint bug
    // [nativeWindow setStyleMask:[nativeWindow styleMask] | NSFullSizeContentViewWindowMask | NSWindowTitleHidden];
    [nativeWindow setTitlebarAppearsTransparent:YES];
    [nativeWindow setMovableByWindowBackground:YES];
}

void DesktopApplication::dockClickedCallback()
{
    emit dockClicked();
}