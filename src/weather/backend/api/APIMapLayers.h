/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_APIMAPLAYERS_H_
#define VREMENAR_APIMAPLAYERS_H_

#include "weather/common/Weather.h"
#include "weather/backend/api/APIRequest.h"

namespace Vremenar
{
namespace Backend
{

APIRequest mapImage(const QString &url);
APIRequest mapForecast();
APIRequest mapForecastDetails(const QString &url);
APIRequest mapLayers(Weather::MapType type);

} // namespace Backend
} // namespace Vremenar

#endif // VREMENAR_APIMAPLAYERS_H_
