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

#include <FirebaseMessaging/FirebaseMessaging.h>

#include "application/NotificationsManager.h"

namespace Vremenar
{

void NotificationsManager::nativeEnabledCheck()
{
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    [center getNotificationSettingsWithCompletionHandler:^(UNNotificationSettings *settings) {
      switch (settings.authorizationStatus) {
      case UNAuthorizationStatusAuthorized:
          emit nativeEnabledStatus(true);
          break;
      case UNAuthorizationStatusDenied:
      case UNAuthorizationStatusNotDetermined:
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

} // namespace Vremenar
