/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_APISTATIONS_H_
#define VREMENAR_APISTATIONS_H_

#include "weather/api/APIRequest.h"

#include <QtCore/QString>
#include <QtPositioning/QGeoCoordinate>

namespace Vremenar::API
{

APIRequest stations(const QGeoCoordinate &coordinate);
APIRequest stations(const QString &string);
APIRequest stationWeatherCondition(const QString &id);
APIRequest stationsList();
APIRequest stationsMap(const QString &url);

} // namespace Vremenar::API

#endif // VREMENAR_APISTATIONS_H_
