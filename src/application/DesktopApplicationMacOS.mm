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

#include <QtCore/QDebug>
#include <QtGui/QWindow>

#include <objc/message.h>

#include <ApplicationServices/ApplicationServices.h>
#include <Cocoa/Cocoa.h>

#define VREMENAR_OBJC
#include "application/ApplicationDelegateMacOS.h"
#include "application/ApplicationDelegateMacOSWrapper.h"
#include "application/DesktopApplication.h"

namespace Vremenar
{

DesktopApplication DesktopApplication::init(int &argc,
                                            char **argv)
{
    if (VremenarDelegate::getInstance().ptr() == nullptr) {
        VremenarApplicationDelegate *delegate = [[VremenarApplicationDelegate alloc] init];

        NSApplication *application = [NSApplication sharedApplication];
        [application setDelegate:delegate];

        VremenarDelegate::getInstance().setPtr(delegate);
    }

    return DesktopApplication(argc, argv);
}

bool dockClickHandler(id self,
                      SEL cmd,
                      ...)
{
    Q_UNUSED(self)
    Q_UNUSED(cmd)

    qobject_cast<DesktopApplication *>(QCoreApplication::instance())->dockClickedCallback();

    return true;
}

bool DesktopApplication::isDark()
{
    if (@available(macOS 10.14, *)) {
        NSAppearanceName basicAppearance = [[NSAppearance currentAppearance] bestMatchFromAppearancesWithNames:@[
            NSAppearanceNameAqua,
            NSAppearanceNameDarkAqua
        ]];
        return [basicAppearance isEqualToString:NSAppearanceNameDarkAqua] != 0;
    }

    return false;
}

bool DesktopApplication::supportsSFSymbols()
{
    if (@available(macOS 11.0, *)) {
        return true;
    } else {
        return false;
    }
}

void DesktopApplication::setupDockHandler()
{
    NSApplication *appInst = [NSApplication sharedApplication];

    if (appInst != nullptr) {
        Class delClass = [[appInst delegate] class];
        SEL shouldHandle = sel_registerName("applicationShouldHandleReopen:hasVisibleWindows:");
        if (class_getInstanceMethod(delClass, shouldHandle) != nullptr) {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            if (class_replaceMethod(delClass, shouldHandle, reinterpret_cast<IMP>(dockClickHandler), "B@:") != nullptr) {
                qDebug() << "Registered dock click handler (replaced original method)";
            } else {
                qWarning() << "Failed to replace method for dock click handler";
            }
        } else {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            if (class_addMethod(delClass, shouldHandle, reinterpret_cast<IMP>(dockClickHandler), "B@:") != 0) {
                qDebug() << "Registered dock click handler";
            } else {
                qWarning() << "Failed to register dock click handler";
            }
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
    if (active != 0) {
        // Workaround buggy behavior of TransformProcessType.
        // http://stackoverflow.com/questions/7596643/
        NSArray *runningApps = [NSRunningApplication
            runningApplicationsWithBundleIdentifier:@"com.apple.dock"];
        NSRunningApplication *app = nullptr;
        for (app in runningApps) {
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
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
        auto nativeView = reinterpret_cast<NSView *>(window->winId());
        NSWindow *nativeWindow = [nativeView window];
        [nativeWindow setCanHide:NO];
    }

    ProcessSerialNumber psn = {0, kCurrentProcess};
    TransformProcessType(&psn, kProcessTransformToUIElementApplication);

    qDebug() << "Dock icon hidden";
}

void DesktopApplication::setupTitleBarLessWindow(quintptr winId,
                                                 qreal /* devicePixelRatio */)
{
    if (winId == 0) {
        return;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
    auto nativeView = reinterpret_cast<NSView *>(winId);
    NSWindow *nativeWindow = [nativeView window];

    [nativeWindow setStyleMask:[nativeWindow styleMask] | NSWindowStyleMaskFullSizeContentView | NSWindowTitleHidden];
    [nativeWindow setTitlebarAppearsTransparent:YES];
}

void DesktopApplication::dockClickedCallback()
{
    emit dockClicked();
}

} // namespace Vremenar
