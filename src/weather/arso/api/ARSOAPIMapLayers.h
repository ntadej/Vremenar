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

#ifndef VREMENAR_ARSOAPIMAPLAYERS_H_
#define VREMENAR_ARSOAPIMAPLAYERS_H_

#include "weather/arso/api/ARSOAPIRequest.h"
#include "weather/common/Weather.h"

namespace Vremenar
{
namespace ARSO
{

APIRequest mapLayers(Weather::MapType type);

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOAPIMAPLAYERS_H_
