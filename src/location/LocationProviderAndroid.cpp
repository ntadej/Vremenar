/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtCore/QDebug>

#include "location/LocationProvider.h"

namespace Vremenar
{

bool LocationProvider::initAndroid()
{
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (!activity.isValid()) {
        qFatal("Android activity could not be loaded!");
    }

    auto isFireTV = activity.callMethod<jboolean>("isFireTV");
    if (isFireTV) {
        qDebug() << "Disabling positioning services on Fire TV.";
        return false;
    }

    return true;
}

} // namespace Vremenar
