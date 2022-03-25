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

#ifndef VREMENAR_MOBILE
#include <AppKit/AppKit.h>
#else
#include <UIKit/UIKit.h>
#endif

#include <FirebaseMessaging/FirebaseMessaging.h>

#define VREMENAR_OBJC
#include "application/NotificationsManager.h"

#ifndef VREMENAR_MOBILE
#include "application/ApplicationDelegateMacOS.h"
#include "application/ApplicationDelegateMacOSWrapper.h"
#include "application/DesktopApplication.h"
#else
#include "application/ApplicationDelegateIOS.h"
#endif

namespace Vremenar
{

bool NotificationsManager::nativeSupported() const
{
    return true;
}

void NotificationsManager::nativeEnabledCheck()
{
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    [center getNotificationSettingsWithCompletionHandler:^(UNNotificationSettings *settings) {
      switch (settings.authorizationStatus) {
      case UNAuthorizationStatusAuthorized:
      case UNAuthorizationStatusNotDetermined:
          emit nativeEnabledStatus(true);
          break;
      case UNAuthorizationStatusDenied:
          emit nativeEnabledStatus(false);
          break;
      default:
          break;
      }
    }];
}

void NotificationsManager::nativeSubscribe(const QString &id) const
{
    [[FIRMessaging messaging] subscribeToTopic:id.toNSString()
                                    completion:^(NSError *_Nullable error) {
                                      if (error != nullptr) {
                                          qDebug() << "Notifications:"
                                                   << "Error" << error.code
                                                   << QString::fromNSString(error.localizedDescription);
                                      }
                                    }];
}

void NotificationsManager::nativeUnsubscribe(const QString &id) const
{
    [[FIRMessaging messaging] unsubscribeFromTopic:id.toNSString()
                                        completion:^(NSError *_Nullable error) {
                                          if (error != nullptr) {
                                              qDebug() << "Notifications:"
                                                       << "Error" << error.code
                                                       << QString::fromNSString(error.localizedDescription);
                                          }
                                        }];
}

bool NotificationsManager::nativeSetup()
{
#ifndef VREMENAR_MOBILE
    auto *applicationDelegate = VremenarDelegate::getInstance().ptr();
    return [applicationDelegate requestNotifications];
#else
    auto *applicationDelegate = (QIOSApplicationDelegate *)([[UIApplication sharedApplication] delegate]);
    return [applicationDelegate requestNotifications];
#endif
}

} // namespace Vremenar
