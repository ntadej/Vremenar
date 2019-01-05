/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/Weather.h"

namespace Vremenar
{

QString Weather::mapTypeString(MapType type)
{
    switch (type) {
    case PrecipitationMap:
        return "precipitaion";
    case CloudCoverageMap:
        return "cloud";
    case WindSpeedMap:
        return "wind";
    case TemperatureMap:
        return "temperature";
    case HailProbabilityMap:
        return "hail";
    }

    return QString();
}

QString Weather::mapTypeStringLocale(MapType type)
{
    switch (type) {
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
    }

    return QString();
}

} // namespace Vremenar
