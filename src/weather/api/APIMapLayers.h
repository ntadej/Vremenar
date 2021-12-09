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

#ifndef VREMENAR_APIMAPLAYERS_H_
#define VREMENAR_APIMAPLAYERS_H_

#include "weather/Weather.h"
#include "weather/api/APIRequest.h"

namespace Vremenar::API
{

APIRequest mapImage(const QString &url);
APIRequest mapLayers(Weather::MapType type);
APIRequest mapLegends();
APIRequest mapTypes();

} // namespace Vremenar::API

#endif // VREMENAR_APIMAPLAYERS_H_
