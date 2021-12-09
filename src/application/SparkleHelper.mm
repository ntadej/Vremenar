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

#include <QtCore/QDebug>

#define VREMENAR_SPARKLE
#include "application/SparkleHelper.h"

namespace Vremenar
{

SparkleHelper::SparkleHelper()
    : sharedUpdater([[SUUpdater alloc] init])
{
}

void SparkleHelper::checkForUpdates()
{
    qDebug() << "Update check requested";

    [sharedUpdater checkForUpdates:nullptr];
}

} // namespace Vremenar
