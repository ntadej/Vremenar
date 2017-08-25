/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/arso/api/ARSOAPICommon.h"

QString Vremenar::ARSO::baseUrl()
{
    return "";
}

QString Vremenar::ARSO::apiUrl()
{
    return baseUrl() + "/api/1.0";
}