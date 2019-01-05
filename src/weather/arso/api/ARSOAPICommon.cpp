/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/arso/api/ARSOAPICommon.h"

#include "Config.h"

namespace Vremenar
{

QString ARSO::baseUrl()
{
    return QString(ARSO_API_ENDPOINT);
}

QString ARSO::apiUrl()
{
    return baseUrl() + "/api/1.0";
}

} // namespace Vremenar
