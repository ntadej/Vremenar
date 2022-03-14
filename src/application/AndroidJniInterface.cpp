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

#include <jni.h>

#include "application/AndroidJniInterface.h"
#include "application/NotificationsManagerAndroid.h"
#include "application/analytics/AnalyticsEngineAndroid.h"

JNIEXPORT jint JNI_OnLoad(JavaVM *vm,
                          void * /* reserved */)
{
    JNIEnv *env{};
    // get the JNIEnv pointer.
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) { // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        return JNI_ERR;
    }

    qDebug() << "Registering native methods";

    // search for Java class which declares the native methods
    jclass javaClassNotifications = env->FindClass("si/tano/vremenar/VremenarNotificationsNativeInterface");
    if (javaClassNotifications == nullptr) {
        return JNI_ERR;
    }

    static JNINativeMethod methodsNotifications[] = {
        {"notificationsSetupCompleted",
         "()V",
         reinterpret_cast<void *>(Vremenar::Android::notificationsSetupCompleted)}}; // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    // register our native methods
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    if (env->RegisterNatives(javaClassNotifications, methodsNotifications, sizeof(methodsNotifications) / sizeof(JNINativeMethod)) != JNI_OK) {
        qWarning() << "Failure!";
        return JNI_ERR;
    }

    // search for Java class which declares the native methods
    jclass javaClassCountly = env->FindClass("si/tano/vremenar/VremenarCountlyNativeInterface");
    if (javaClassCountly == nullptr) {
        return JNI_ERR;
    }

    static JNINativeMethod methodsCountly[] = {
        {"appKey",
         "()Ljava/lang/String;",
         reinterpret_cast<void *>(Vremenar::Android::countlyAppKey)}, // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        {"endpoint",
         "()Ljava/lang/String;",
         reinterpret_cast<void *>(Vremenar::Android::countlyEndpoint)}, // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        {"salt",
         "()Ljava/lang/String;",
         reinterpret_cast<void *>(Vremenar::Android::countlySalt)}}; // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

    // register our native methods
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    if (env->RegisterNatives(javaClassCountly, methodsCountly, sizeof(methodsCountly) / sizeof(JNINativeMethod)) != JNI_OK) {
        qWarning() << "Failure!";
        return JNI_ERR;
    }

    qDebug() << "Success!";

    return JNI_VERSION_1_6;
}

namespace Vremenar::Android
{

QAndroidJniObject activity()
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (!activity.isValid()) {
        qFatal("Android activity could not be loaded!"); // NOLINT(cppcoreguidelines-pro-type-vararg)
    }
    return activity;
}

} // namespace Vremenar::Android
