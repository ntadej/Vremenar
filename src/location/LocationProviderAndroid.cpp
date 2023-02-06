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
#include <QtCore/QJniObject>

#include "location/LocationProvider.h"

namespace Vremenar
{

bool LocationProvider::initAndroid()
{
    const QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;"); // NOLINT(cppcoreguidelines-pro-type-vararg)
    if (!activity.isValid()) {
        qFatal("Android activity could not be loaded!"); // NOLINT(cppcoreguidelines-pro-type-vararg)
    }

    const auto isFireTV = static_cast<bool>(activity.callMethod<jboolean>("isFireTV")); // NOLINT(cppcoreguidelines-pro-type-vararg)
    if (isFireTV) {
        qDebug() << "Disabling positioning services on Fire TV.";
        return false;
    }

    return true;
}

} // namespace Vremenar
