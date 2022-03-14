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

#ifndef VREMENAR_ANALYTICSENGINEANDROID_H_
#define VREMENAR_ANALYTICSENGINEANDROID_H_

#include "application/analytics/AnalyticsEngine.h"

#include <jni.h>

namespace Vremenar
{

namespace Android
{

jstring countlyAppKey(JNIEnv *env,
                      jobject obj);

jstring countlyEndpoint(JNIEnv *env,
                        jobject obj);

jstring countlySalt(JNIEnv *env,
                    jobject obj);

} // namespace Android

class AnalyticsEngineAndroid : public AnalyticsEngine
{
public:
    AnalyticsEngineAndroid();

    [[nodiscard]] bool manualSessionHandling() const override { return false; }

    void beginSession() const override {}
    void updateSession() const override {}
    void endSession() const override {}

    void recordEvent(const QString &event) const override;
};

} // namespace Vremenar

#endif // VREMENAR_ANALYTICSENGINEANDROID_H_
