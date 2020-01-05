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

#ifndef VREMENAR_ARSOAPILOCATIONS_H_
#define VREMENAR_ARSOAPILOCATIONS_H_

#include <QtPositioning/QGeoCoordinate>

#include "weather/arso/api/ARSOAPIRequest.h"

namespace Vremenar
{
namespace ARSO
{

APIRequest location(const QGeoCoordinate &coordinate);

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOAPILOCATIONS_H_
