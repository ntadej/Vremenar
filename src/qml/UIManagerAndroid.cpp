/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
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
#include <QtGui/QScreen>

#include "qml/UIManager.h"

namespace Vremenar
{

Common::DeviceType Qml::UIManager::getDeviceTypeAndroid()
{
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (!activity.isValid()) {
        qFatal("Android activity could not be loaded!");
    }

    auto isFireTV = activity.callMethod<jboolean>("isFireTV");
    if (isFireTV) {
        return Common::FireTV;
    }

    auto isAndroidTV = activity.callMethod<jboolean>("isAndroidTV");
    if (isAndroidTV) {
        return Common::AndroidTV;
    }

    return Common::Android;
}

QMargins Qml::UIManager::safeAreaMargins()
{
    QAndroidJniEnvironment env;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (!activity.isValid()) {
        qFatal("Android activity could not be loaded!");
    }

    auto m = activity.callObjectMethod<jintArray>("getSafeAreMargins");

    jint *mArray = env->GetIntArrayElements(m.object<jintArray>(), nullptr);

    QMargins margins;
    margins.setTop(static_cast<int>(mArray[0] / _currentPrimaryScreen->devicePixelRatio()));
    margins.setBottom(static_cast<int>(mArray[1] / _currentPrimaryScreen->devicePixelRatio()));
    margins.setLeft(static_cast<int>(mArray[2] / _currentPrimaryScreen->devicePixelRatio()));
    margins.setRight(static_cast<int>(mArray[3] / _currentPrimaryScreen->devicePixelRatio()));

    env->ReleaseIntArrayElements(m.object<jintArray>(), mArray, JNI_ABORT);

    return margins;
}

} // namespace Vremenar
