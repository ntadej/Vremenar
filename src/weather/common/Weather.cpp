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
    if (type == QStringLiteral("historical")) {
        return Weather::Historical;
    }
    if (type == QStringLiteral("forecast")) {
        return Weather::Forecast;
    }

    return Weather::Recent;
}

Weather::MapType Weather::mapTypeFromString(const QString &type)
{
    if (type == QStringLiteral("condition")) {
        return Weather::WeatherConditionMap;
    }
    if (type == QStringLiteral("precipitation")) {
        return Weather::PrecipitationMap;
    }
    if (type == QStringLiteral("cloud")) {
        return Weather::CloudCoverageMap;
    }
    if (type == QStringLiteral("wind")) {
        return Weather::WindSpeedMap;
    }
    if (type == QStringLiteral("temperature")) {
        return Weather::TemperatureMap;
    }
    if (type == QStringLiteral("hail")) {
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
    if (type == QStringLiteral("image")) {
        return Weather::ImageRendering;
    }
    if (type == QStringLiteral("tiles")) {
        return Weather::TilesRendering;
    }

    return Weather::ImageRendering;
}

} // namespace Vremenar
