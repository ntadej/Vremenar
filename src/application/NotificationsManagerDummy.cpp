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

#include "application/NotificationsManager.h"

namespace Vremenar
{

bool NotificationsManager::nativeSupported() const
{
    return false;
}

void NotificationsManager::nativeEnabledCheck()
{
}

void NotificationsManager::nativeSubscribe(const QString &id) const
{
    Q_UNUSED(id);
}

void NotificationsManager::nativeUnsubscribe(const QString &id) const
{
    Q_UNUSED(id);
}

bool NotificationsManager::nativeSetup()
{
    return true;
}

} // namespace Vremenar
