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

#include <QtCore/QDebug>

#include "application/SparkleHelper.h"

#include "Config.h"

#include <winsparkle.h>

namespace Vremenar
{

SparkleHelper::SparkleHelper()
{
    QString url(Vremenar::AppCastEndpoint);
    url.append(QStringLiteral("/appcast.xml"));

    win_sparkle_set_appcast_url(url.toStdString().c_str());
    win_sparkle_set_eddsa_pub_base64("U2gUlDA3cZYnWfAWTj0qxF30XqWVl0hGbOFDP3sNZIw=");
    win_sparkle_init();
}

SparkleHelper::~SparkleHelper()
{
    win_sparkle_cleanup();
}

void SparkleHelper::checkForUpdates()
{
    qDebug() << "Update check requested";

    win_sparkle_check_update_with_ui();
}

} // namespace Vremenar
