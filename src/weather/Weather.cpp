/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/Weather.h"

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

Weather::MapStyle Weather::mapStyleFromString(const QString &style)
{
    if (style == QStringLiteral("satellite")) {
        return Weather::SatelliteMapStyle;
    }
    if (style == QStringLiteral("streets-light")) {
        return Weather::StreetsLightMapStyle;
    }
    if (style == QStringLiteral("streets-dark")) {
        return Weather::StreetsDarkMapStyle;
    }

    return Weather::UnknownMapStyle;
}

QString Weather::mapStyleToString(MapStyle style)
{
    switch (style) {
    case SatelliteMapStyle:
        return QStringLiteral("satellite");
    case StreetsLightMapStyle:
        return QStringLiteral("streets-light");
    case StreetsDarkMapStyle:
        return QStringLiteral("streets-dark");
    case UnknownMapStyle:
        return {};
    }

    return {};
}

QString Weather::mapStyleToLocalizedString(MapStyle style)
{
    switch (style) {
    case SatelliteMapStyle:
        return QObject::tr("Satellite");
    case StreetsLightMapStyle:
        return QObject::tr("Streets (Light)");
    case StreetsDarkMapStyle:
        return QObject::tr("Streets (Dark)");
    case UnknownMapStyle:
        return {};
    }

    return {};
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
    if (type == QStringLiteral("uv_index_max")) {
        return Weather::UVIndexMaxMap;
    }
    if (type == QStringLiteral("uv_dose")) {
        return Weather::UVDoseMap;
    }

    return Weather::UnknownMapType;
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
    case UVIndexMaxMap:
        return QStringLiteral("uv_index_max");
    case UVDoseMap:
        return QStringLiteral("uv_dose");
    case UnknownMapType:
        return {};
    }

    return {};
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
    case UVIndexMaxMap:
        return QObject::tr("Maximum daily UV index");
    case UVDoseMap:
        return QObject::tr("Total daily UV dose");
    case UnknownMapType:
        return {};
    }

    return {};
}

Weather::MapRenderingType Weather::mapRenderingTypeFromString(const QString &type)
{
    if (type == QStringLiteral("image")) {
        return Weather::ImageRendering;
    }
    if (type == QStringLiteral("tiles")) {
        return Weather::TilesRendering;
    }
    if (type == QStringLiteral("icons")) {
        return Weather::IconsRendering;
    }

    return Weather::ImageRendering;
}

} // namespace Vremenar
