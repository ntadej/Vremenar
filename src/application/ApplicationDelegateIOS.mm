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

#include <UIKit/UIKit.h>

#include <FirebaseCore/FirebaseCore.h>
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
@end

// Initialise
@implementation QIOSApplicationDelegate (NotificationsApplicationDelegate)

NSString *const kGCMMessageIDKey = @"gcm.message_id";

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    Q_UNUSED(launchOptions)

    auto notificationCenter = [UNUserNotificationCenter currentNotificationCenter];
    notificationCenter.delegate = self;
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
                                            [FIRApp configure];
                                            [FIRMessaging messaging].delegate = self;
                                            [application registerForRemoteNotifications];
                                        } else {
                                            qDebug() << "Notifications:"
                                                     << "not allowed";
                                        }
                                      }];
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    application.applicationIconBadgeNumber = 0;
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    qDebug() << "Notifications:"
             << "APNs device token retrieved";

    [FIRMessaging messaging].APNSToken = deviceToken;
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    qDebug() << "Notifications:"
             << "Unable to register for remote notifications" << error.code
             << QString::fromNSString(error.localizedDescription);
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
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

    if (@available(iOS 14.0, *)) {
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
