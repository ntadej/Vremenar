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

#ifndef VREMENAR_COMMON_H_
#define VREMENAR_COMMON_H_

#include <QtPositioning/QGeoRectangle>

namespace Vremenar
{
namespace Backend
{

constexpr qreal minZoomLevel{7.5};
constexpr qreal maxZoomLevel{11};

QGeoRectangle defaultMapCoordinates();

} // namespace Backend
} // namespace Vremenar

#endif // VREMENAR_COMMON_H_
