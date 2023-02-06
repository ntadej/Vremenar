/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QDebug>
#include <QtCore/QJniEnvironment>
#include <QtCore/QJniObject>

#include "application/AndroidJniInterface.h"
#include "application/NotificationsManager.h"
#include "application/NotificationsManagerAndroid.h"
#include "application/Services.h"

namespace Vremenar::Android
{

void notificationsSetupCompleted(JNIEnv * /* env */,
                                 jobject /* obj */)
{
    auto *manager = Services::getInstance().notificationsManager();
    if (manager != nullptr) {
        manager->nativeInitCompleted();
    }
}

} // namespace Vremenar::Android

namespace Vremenar
{

bool NotificationsManager::nativeSupported() const
{
    const QJniObject activity = Vremenar::Android::activity();

    const auto isFireTV = static_cast<bool>(activity.callMethod<jboolean>("isFireTV"));
    const auto isAndroidTV = static_cast<bool>(activity.callMethod<jboolean>("isAndroidTV"));
    if (isFireTV || isAndroidTV) {
        return false;
    }

    return static_cast<bool>(activity.callMethod<jboolean>("areNotificationsSupported"));
}

void NotificationsManager::nativeEnabledCheck()
{
    const QJniObject activity = Vremenar::Android::activity();

    const auto result = static_cast<bool>(activity.callMethod<jboolean>("areNotificationsEnabled"));
    emit nativeEnabledStatus(result);
}

void NotificationsManager::nativeSubscribe(const QString &id) const
{
    const QJniObject activity = Vremenar::Android::activity();

    const QJniEnvironment env;
    jstring arg = env->NewStringUTF(id.toLatin1().data());
    activity.callMethod<void>("notificationsSubscribe", "(Ljava/lang/String;)V", arg); // NOLINT(cppcoreguidelines-pro-type-vararg)
}

void NotificationsManager::nativeUnsubscribe(const QString &id) const
{
    const QJniObject activity = Vremenar::Android::activity();

    const QJniEnvironment env;
    jstring arg = env->NewStringUTF(id.toLatin1().data());
    activity.callMethod<void>("notificationsUnsubscribe", "(Ljava/lang/String;)V", arg); // NOLINT(cppcoreguidelines-pro-type-vararg)
}

bool NotificationsManager::nativeSetup()
{
    const QJniObject activity = Vremenar::Android::activity();

    return static_cast<bool>(activity.callMethod<jboolean>("requestNotifications"));
}

} // namespace Vremenar
