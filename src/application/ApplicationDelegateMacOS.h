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

#ifndef VREMENAR_APPLICATIONDELEGATEMACOS_H_
#define VREMENAR_APPLICATIONDELEGATEMACOS_H_

#include <FirebaseMessaging/FirebaseMessaging.h>

#include <AppKit/AppKit.h>
#include <UserNotifications/UserNotifications.h>

@interface VremenarApplicationDelegate : NSObject <NSApplicationDelegate, UNUserNotificationCenterDelegate, FIRMessagingDelegate>
- (bool)requestNotifications;
@end

#endif // VREMENAR_APPLICATIONDELEGATEMACOS_H_
