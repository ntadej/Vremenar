/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtCore/QDebug>
#include <jni.h>

#include "application/analytics/AnalyticsEngineAndroid.h"

#include "Config.h"

namespace Vremenar::Android
{

static jstring countlyAppKey(JNIEnv *env,
                             jobject /*obj*/)
{
    return env->NewStringUTF(Vremenar::CountlyAppKey.data());
}

static jstring countlyEndpoint(JNIEnv *env,
                               jobject /*obj*/)
{
    return env->NewStringUTF(Vremenar::CountlyEndpoint.data());
}

static jstring countlySalt(JNIEnv *env,
                           jobject /*obj*/)
{
    return env->NewStringUTF(Vremenar::CountlySalt.data());
}

} // namespace Vremenar::Android

static JNINativeMethod methods[] = {
    {"appKey",
     "()Ljava/lang/String;",
     (void *)Vremenar::Android::countlyAppKey},
    {"endpoint",
     "()Ljava/lang/String;",
     (void *)Vremenar::Android::countlyEndpoint},
    {"salt",
     "()Ljava/lang/String;",
     (void *)Vremenar::Android::countlySalt}};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm,
                          void * /* reserved */)
{
    JNIEnv *env;
    // get the JNIEnv pointer.
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // search for Java class which declares the native methods
    jclass javaClass = env->FindClass("si/tano/vremenar/VremenarCountlyNativeInterface");
    if (!javaClass) {
        return JNI_ERR;
    }

    qDebug() << "Registering native methods";

    // register our native methods
    if (env->RegisterNatives(javaClass, methods,
                             sizeof(methods) / sizeof(methods[0]))
        < 0) {
        qWarning() << "Failure!";
        return JNI_ERR;
    }

    qDebug() << "Success!";

    return JNI_VERSION_1_6;
}

namespace Vremenar
{

AnalyticsEngineAndroid::AnalyticsEngineAndroid() {}

void AnalyticsEngineAndroid::recordEvent(const QString &event) const
{
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (!activity.isValid()) {
        qFatal("Android activity could not be loaded!");
    }

    QAndroidJniEnvironment env;
    jstring arg = env->NewStringUTF(event.toLatin1().data());
    activity.callMethod<void>("recordEvent", "(Ljava/lang/String;)V", arg);
}

} // namespace Vremenar
