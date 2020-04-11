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

#ifndef VREMENAR_WEATHER_H_
#define VREMENAR_WEATHER_H_

#include <QtCore/QObject>

namespace Vremenar::Weather
{

Q_NAMESPACE

enum MapType {
    UnknownMap,
    ForecastMap,
    PrecipitationMap,
    CloudCoverageMap,
    WindSpeedMap,
    TemperatureMap,
    HailProbabilityMap
};

Q_ENUM_NS(MapType)

QString mapTypeString(Vremenar::Weather::MapType type);
Q_INVOKABLE QString mapTypeStringLocale(Vremenar::Weather::MapType type);

} // namespace Vremenar::Weather

#endif // VREMENAR_WEATHER_H_
