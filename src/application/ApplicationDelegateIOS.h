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

#ifndef VREMENAR_APPLICATIONDELEGATEIOS_H_
#define VREMENAR_APPLICATIONDELEGATEIOS_H_

#include <UIKit/UIKit.h>
#include <UserNotifications/UserNotifications.h>

#include <FirebaseMessaging/FirebaseMessaging.h>

/*
* Override UIApplicationDelegate by adding a category to the QIOApplicationDelegate.
* The only way to do that even if it's a bit like hacking the Qt stuff
* See: https://bugreports.qt-project.org/browse/QTBUG-38184
*/
@interface QIOSApplicationDelegate : NSObject <UIApplicationDelegate, UNUserNotificationCenterDelegate, FIRMessagingDelegate>
@end

// Add a category to QIOSApplicationDelegate
@interface QIOSApplicationDelegate (NotificationsApplicationDelegate)
- (bool)requestNotifications;
@end

#endif // VREMENAR_APPLICATIONDELEGATEIOS_H_
