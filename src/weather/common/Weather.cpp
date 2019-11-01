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

#include "weather/common/Weather.h"

namespace Vremenar
{

QString Weather::mapTypeString(MapType type)
{
    switch (type) {
    case ForecastMap:
        return QStringLiteral("forecast");
    case PrecipitationMap:
        return QStringLiteral("precipitaion");
    case CloudCoverageMap:
        return QStringLiteral("cloud");
    case WindSpeedMap:
        return QStringLiteral("wind");
    case TemperatureMap:
        return QStringLiteral("temperature");
    case HailProbabilityMap:
        return QStringLiteral("hail");
    case UnknownMap:
        return QString();
    }

    return QString();
}

QString Weather::mapTypeStringLocale(MapType type)
{
    switch (type) {
    case ForecastMap:
        return QObject::tr("Forecast");
    case PrecipitationMap:
        return QObject::tr("Precipitation");
    case CloudCoverageMap:
        return QObject::tr("Cloud coverage");
    case WindSpeedMap:
        return QObject::tr("Wind speed");
    case TemperatureMap:
        return QObject::tr("Temperature");
    case HailProbabilityMap:
        return QObject::tr("Hail probability");
    case UnknownMap:
        return QString();
    }

    return QString();
}

} // namespace Vremenar
