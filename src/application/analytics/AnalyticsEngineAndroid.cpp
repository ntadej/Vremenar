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

#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtCore/QDebug>

#include "application/AndroidJniInterface.h"
#include "application/analytics/AnalyticsEngineAndroid.h"

#include "Config.h"

namespace Vremenar::Android
{

jstring countlyAppKey(JNIEnv *env,
                      jobject /*obj*/)
{
    return env->NewStringUTF(Vremenar::CountlyAppKey.data());
}

jstring countlyEndpoint(JNIEnv *env,
                        jobject /*obj*/)
{
    return env->NewStringUTF(Vremenar::CountlyEndpoint.data());
}

jstring countlySalt(JNIEnv *env,
                    jobject /*obj*/)
{
    return env->NewStringUTF(Vremenar::CountlySalt.data());
}

} // namespace Vremenar::Android

namespace Vremenar
{

AnalyticsEngineAndroid::AnalyticsEngineAndroid() = default;

void AnalyticsEngineAndroid::recordEvent(const QString &event) const
{
    QAndroidJniObject activity = Vremenar::Android::activity();

    QAndroidJniEnvironment env;
    jstring arg = env->NewStringUTF(event.toLatin1().data());
    activity.callMethod<void>("recordEvent", "(Ljava/lang/String;)V", arg); // NOLINT(cppcoreguidelines-pro-type-vararg)
}

} // namespace Vremenar
