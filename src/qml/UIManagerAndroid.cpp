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

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QJniEnvironment>
#include <QtCore/QJniObject>
#include <QtGui/QScreen>

#include "application/AndroidJniInterface.h"
#include "qml/UIManager.h"

namespace Vremenar
{

Common::DeviceType Qml::UIManager::getDeviceTypeAndroid()
{
    const QJniObject activity = Vremenar::Android::activity();

    const auto isFireTV = static_cast<bool>(activity.callMethod<jboolean>("isFireTV")); // NOLINT(cppcoreguidelines-pro-type-vararg)
    if (isFireTV) {
        return Common::FireTV;
    }

    const auto isAndroidTV = static_cast<bool>(activity.callMethod<jboolean>("isAndroidTV")); // NOLINT(cppcoreguidelines-pro-type-vararg)
    if (isAndroidTV) {
        return Common::AndroidTV;
    }

    return Common::Android;
}

QMargins Qml::UIManager::safeAreaMargins()
{
    const QJniObject activity = Vremenar::Android::activity();

    const auto m = activity.callObjectMethod<jintArray>("getSafeAreMargins");

    const QJniEnvironment env;
    jint *mArray = env->GetIntArrayElements(m.object<jintArray>(), nullptr);

    QMargins margins;
    margins.setTop(static_cast<int>(mArray[0] / _currentPrimaryScreen->devicePixelRatio()));    // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    margins.setBottom(static_cast<int>(mArray[1] / _currentPrimaryScreen->devicePixelRatio())); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    margins.setLeft(static_cast<int>(mArray[2] / _currentPrimaryScreen->devicePixelRatio()));   // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    margins.setRight(static_cast<int>(mArray[3] / _currentPrimaryScreen->devicePixelRatio()));  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    env->ReleaseIntArrayElements(m.object<jintArray>(), mArray, JNI_ABORT);

    return margins;
}

void Qml::UIManager::toastAndroid(const QString &message)
{
    // all the magic must happen on Android UI thread
    QNativeInterface::QAndroidApplication::runOnAndroidMainThread([message] {
        const QJniObject javaString = QJniObject::fromString(message);
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        const QJniObject toast = QJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                    "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                    QNativeInterface::QAndroidApplication::context(),
                                                                    javaString.object(),
                                                                    static_cast<jint>(0));
        toast.callMethod<void>("show");
    });
}

} // namespace Vremenar
