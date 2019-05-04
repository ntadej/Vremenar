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

#include "weather/arso/api/ARSOAPICommon.h"

#include "Config.h"

namespace Vremenar
{

QString ARSO::apiUrl()
{
    return QStringLiteral(ARSO_API_ENDPOINT) + "/api/1.0";
}

QString ARSO::resourcesUrl()
{
    return QStringLiteral(ARSO_API_RESOURCES);
}

} // namespace Vremenar
