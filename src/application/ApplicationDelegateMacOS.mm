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

#include <AppKit/AppKit.h>

#include <FirebaseCore/FirebaseCore.h>
#include <FirebaseMessaging/FirebaseMessaging.h>

#include "application/ApplicationDelegateMacOS.h"

@implementation VremenarApplicationDelegate {
    bool _notificationsRequested;
}

NSString *const kGCMMessageIDKey = @"gcm.message_id";

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    Q_UNUSED(notification);

    [UNUserNotificationCenter currentNotificationCenter].delegate = self;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    Q_UNUSED(notification);

    [self requestNotifications];
}

- (void)requestNotifications
{
    if (_notificationsRequested) {
        return;
    }

    auto notificationCenter = [UNUserNotificationCenter currentNotificationCenter];
    UNAuthorizationOptions opts = UNAuthorizationOptionAlert | UNAuthorizationOptionBadge | UNAuthorizationOptionSound;
    [notificationCenter requestAuthorizationWithOptions:opts
                                      completionHandler:^(BOOL granted, NSError *_Nullable error) {
                                        if (error != nullptr) {
                                            qDebug() << "Notifications:"
                                                     << "Error" << error.code
                                                     << QString::fromNSString(error.localizedDescription);
                                        }
                                        if (granted != 0) {
                                            qDebug() << "Notifications:"
                                                     << "allowed";
                                            [FIRApp configure];
                                            [FIRMessaging messaging].delegate = self;
                                            [[NSApplication sharedApplication] registerForRemoteNotifications];
                                        } else {
                                            qDebug() << "Notifications:"
                                                     << "not allowed";
                                        }
                                      }];

    _notificationsRequested = true;
}

- (void)application:(NSApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    qDebug() << "Notifications:"
             << "APNs device token retrieved";

    [FIRMessaging messaging].APNSToken = deviceToken;
}

- (void)application:(NSApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    qDebug() << "Notifications:"
             << "Unable to register for remote notifications" << error.code
             << QString::fromNSString(error.localizedDescription);
}

- (void)application:(NSApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    [[FIRMessaging messaging] appDidReceiveMessage:userInfo];

    if (userInfo[kGCMMessageIDKey] != nullptr) {
        qDebug() << "Notifications:"
                 << "received" << QString::fromNSString(userInfo[kGCMMessageIDKey]);
    } else {
        qDebug() << "Notifications:"
                 << "received";
    }
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center
       willPresentNotification:(UNNotification *)notification
         withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler
{
    NSDictionary *userInfo = notification.request.content.userInfo;
    if (userInfo[kGCMMessageIDKey] != nullptr) {
        qDebug() << "Notifications:"
                 << "will present" << QString::fromNSString(userInfo[kGCMMessageIDKey]);
    } else {
        qDebug() << "Notifications:"
                 << "will present";
    }

    [[FIRMessaging messaging] appDidReceiveMessage:userInfo];

    if (@available(macOS 11.0, *)) {
        completionHandler(UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionBanner);
    } else {
        completionHandler(UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionAlert);
    }
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center
    didReceiveNotificationResponse:(UNNotificationResponse *)response
             withCompletionHandler:(void (^)(void))completionHandler
{
    NSDictionary *userInfo = response.notification.request.content.userInfo;
    if (userInfo[kGCMMessageIDKey] != nullptr) {
        qDebug() << "Notifications:"
                 << "triggered" << QString::fromNSString(userInfo[kGCMMessageIDKey]);
    } else {
        qDebug() << "Notifications:"
                 << "triggered";
    }

    [[FIRMessaging messaging] appDidReceiveMessage:userInfo];

    completionHandler();
}

- (void)messaging:(FIRMessaging *)messaging didReceiveRegistrationToken:(NSString *)fcmToken
{
    qDebug() << "Notifications:"
             << "FCM registration token:"
             << QString::fromNSString(fcmToken);

    NSDictionary *dataDict = [NSDictionary dictionaryWithObject:fcmToken forKey:@"token"];
    [[NSNotificationCenter defaultCenter] postNotificationName:
                                              @"FCMToken"
                                                        object:nil
                                                      userInfo:dataDict];
}

@end
