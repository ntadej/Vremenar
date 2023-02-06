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

#define VREMENAR_OBJC
#include "application/SparkleHelper.h"

namespace Vremenar
{

SparkleHelper::SparkleHelper()
    : updaterController([[SPUStandardUpdaterController alloc] initWithStartingUpdater:TRUE updaterDelegate:nullptr userDriverDelegate:nullptr])
{
}

void SparkleHelper::checkForUpdates()
{
    qDebug() << "Update check requested";

    [updaterController checkForUpdates:nullptr];
}

} // namespace Vremenar
