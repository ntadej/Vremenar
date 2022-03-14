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

#ifndef VREMENAR_NOTIFICATIONSMANAGERANDROID_H_
#define VREMENAR_NOTIFICATIONSMANAGERANDROID_H_

#include <jni.h>

namespace Vremenar::Android
{

void notificationsSetupCompleted(JNIEnv *env,
                                 jobject obj);

} // namespace Vremenar::Android

#endif // VREMENAR_NOTIFICATIONSMANAGERANDROID_H_
