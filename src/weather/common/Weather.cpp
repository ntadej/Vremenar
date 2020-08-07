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

#include "weather/common/Weather.h"

namespace Vremenar
{

Weather::ObservationType Weather::observationTypeFromString(const QString &type)
{
    if (type == "historical") {
        return Weather::Historical;
    }
    if (type == "forecast") {
        return Weather::Forecast;
    }

    return Weather::Recent;
}

Weather::MapType Weather::mapTypeFromString(const QString &type)
{
    if (type == "condition") {
        return Weather::WeatherConditionMap;
    }
    if (type == "precipitation") {
        return Weather::PrecipitationMap;
    }
    if (type == "cloud") {
        return Weather::CloudCoverageMap;
    }
    if (type == "wind") {
        return Weather::WindSpeedMap;
    }
    if (type == "temperature") {
        return Weather::TemperatureMap;
    }
    if (type == "hail") {
        return Weather::HailProbabilityMap;
    }

    return Weather::UnknownMap;
}

QString Weather::mapTypeToString(MapType type)
{
    switch (type) {
    case WeatherConditionMap:
        return QStringLiteral("condition");
    case PrecipitationMap:
        return QStringLiteral("precipitation");
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

QString Weather::mapTypeToLocalizedString(MapType type)
{
    switch (type) {
    case WeatherConditionMap:
        return QObject::tr("Weather condition");
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

Weather::MapRenderingType Weather::mapRenderingTypeFromString(const QString &type)
{
    if (type == "image") {
        return Weather::ImageRendering;
    }
    if (type == "tiles") {
        return Weather::TilesRendering;
    }

    return Weather::ImageRendering;
}

} // namespace Vremenar
