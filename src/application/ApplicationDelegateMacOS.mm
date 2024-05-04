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

#include "application/ApplicationDelegateMacOS.h"

#include "application/NotificationsManager.h"
#include "application/Services.h"
#include "settings/Settings.h"

#include <FirebaseCore/FirebaseCore.h>

#include <QtCore/QDebug>

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

    Vremenar::Settings settings;
    if (settings.notificationsEnabled() && settings.notificationsInitialChoice()) {
        [self requestNotifications];
    }
}

- (bool)requestNotifications
{
    if (_notificationsRequested) {
        return true;
    }

    [FIRApp configure];
    [FIRMessaging messaging].delegate = self;

    auto notificationCenter = [UNUserNotificationCenter currentNotificationCenter];
    UNAuthorizationOptions opts = UNAuthorizationOptionAlert | UNAuthorizationOptionBadge | UNAuthorizationOptionSound;
    [notificationCenter requestAuthorizationWithOptions:opts
                                      completionHandler:^(BOOL granted, NSError *_Nullable error) {
                                        if (error != nullptr) {
                                            qDebug() << "Notifications:"
                                                     << "Error" << error.code
                                                     << QString::fromNSString(error.localizedDescription);
                                        }
                                        if (granted) {
                                            qDebug() << "Notifications:"
                                                     << "allowed";
                                        } else {
                                            qDebug() << "Notifications:"
                                                     << "not allowed";
                                        }
                                      }];

    if (![NSApplication sharedApplication].registeredForRemoteNotifications) {
        qDebug() << "Notifications:"
                 << "Registering application";
        [[NSApplication sharedApplication] registerForRemoteNotifications];
    } else {
        qDebug() << "Notifications:"
                 << "Application already registered";
    }

    _notificationsRequested = true;

    return false;
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

    completionHandler(UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionBanner);
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

    if (fcmToken == nullptr) {
        return;
    }

    NSDictionary *dataDict = [NSDictionary dictionaryWithObject:fcmToken forKey:@"token"];
    [[NSNotificationCenter defaultCenter] postNotificationName:
                                              @"FCMToken"
                                                        object:nil
                                                      userInfo:dataDict];

    auto *manager = Vremenar::Services::getInstance().notificationsManager();
    if (manager != nullptr) {
        manager->nativeInitCompleted();
    }
}

@end
