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

#include "weather/backend/Common.h"

namespace
{
constexpr double DefaultTopLeftLatitude{12.1};
constexpr double DefaultTopLeftLongitude{47.42};
constexpr double DefaultBottomRightLatitude{17.44};
constexpr double DefaultBottomRightLongitude{44.67};
} // namespace

namespace Vremenar::Backend
{

QGeoRectangle defaultMapCoordinates()
{
    return QGeoRectangle(
        QGeoCoordinate(DefaultTopLeftLatitude, DefaultTopLeftLongitude),
        QGeoCoordinate(DefaultBottomRightLatitude, DefaultBottomRightLongitude));
}

} // namespace Vremenar::Backend
