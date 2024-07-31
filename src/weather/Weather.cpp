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

#include "weather/Weather.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <stdexcept>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

QString Weather::dateDisplay(const QDateTime &time)
{
    auto current = QDateTime::currentDateTime();

    const qint64 diff = current.daysTo(time);
    if (diff == 0) {
        return QObject::tr("today");
    }
    if (diff == 1) {
        return QObject::tr("tomorrow");
    }
    if (diff == -1) {
        return QObject::tr("yesterday");
    }

    return QLocale::system().toString(time.date(), QLocale::ShortFormat);
}

QString Weather::timeDisplay(const QDateTime &time)
{
    return QLocale::system().toString(time.time(), QLocale::ShortFormat);
}

Weather::ObservationType Weather::observationTypeFromString(const QString &type)
{
    if (type == "historical"_L1) {
        return Weather::Historical;
    }
    if (type == "forecast"_L1) {
        return Weather::Forecast;
    }

    return Weather::Recent;
}

Weather::MapStyle Weather::mapStyleFromString(const QString &style)
{
    if (style == "satellite"_L1) {
        return Weather::SatelliteMapStyle;
    }
    if (style == "streets-light"_L1) {
        return Weather::StreetsLightMapStyle;
    }
    if (style == "streets-dark"_L1) {
        return Weather::StreetsDarkMapStyle;
    }

    return Weather::UnknownMapStyle;
}

QString Weather::mapStyleToString(MapStyle style)
{
    switch (style) {
    case SatelliteMapStyle:
        return u"satellite"_s;
    case StreetsLightMapStyle:
        return u"streets-light"_s;
    case StreetsDarkMapStyle:
        return u"streets-dark"_s;
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
    if (type == "condition"_L1) {
        return Weather::WeatherConditionMap;
    }
    if (type == "precipitation"_L1) {
        return Weather::PrecipitationMap;
    }
    if (type == "precipitation_global"_L1) {
        return Weather::PrecipitationGlobalMap;
    }
    if (type == "cloud"_L1) {
        return Weather::CloudCoverageMap;
    }
    if (type == "cloud_infrared_global"_L1) {
        return Weather::CloudCoverageInfraredGlobalMap;
    }
    if (type == "wind"_L1) {
        return Weather::WindSpeedMap;
    }
    if (type == "temperature"_L1) {
        return Weather::TemperatureMap;
    }
    if (type == "hail"_L1) {
        return Weather::HailProbabilityMap;
    }
    if (type == "uv_index_max"_L1) {
        return Weather::UVIndexMaxMap;
    }
    if (type == "uv_dose"_L1) {
        return Weather::UVDoseMap;
    }

    return Weather::UnknownMapType;
}

QString Weather::mapTypeToString(MapType type)
{
    switch (type) {
    case WeatherConditionMap:
        return u"condition"_s;
    case PrecipitationMap:
        return u"precipitation"_s;
    case PrecipitationGlobalMap:
        return u"precipitation_global"_s;
    case CloudCoverageMap:
        return u"cloud"_s;
    case CloudCoverageInfraredGlobalMap:
        return u"cloud_infrared_global"_s;
    case WindSpeedMap:
        return u"wind"_s;
    case TemperatureMap:
        return u"temperature"_s;
    case HailProbabilityMap:
        return u"hail"_s;
    case UVIndexMaxMap:
        return u"uv_index_max"_s;
    case UVDoseMap:
        return u"uv_dose"_s;
    case UnknownMapType:
        return u""_s;
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
    case PrecipitationGlobalMap:
        return QObject::tr("Precipitation (global)");
    case CloudCoverageMap:
        return QObject::tr("Cloud coverage");
    case CloudCoverageInfraredGlobalMap:
        return QObject::tr("Cloud coverage (global)");
    case WindSpeedMap:
        return QObject::tr("Wind");
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
    if (type == "image"_L1) {
        return Weather::ImageRendering;
    }
    if (type == "tiles"_L1) {
        return Weather::TilesRendering;
    }
    if (type == "icons"_L1) {
        return Weather::IconsRendering;
    }

    return Weather::UnknownRendering;
}

Weather::AlertType Weather::alertTypeFromString(const QString &type)
{
    if (type == "wind"_L1) {
        return Weather::WindAlert;
    }
    if (type == "snow-ice"_L1) {
        return Weather::SnowIceAlert;
    }
    if (type == "thunderstorm"_L1) {
        return Weather::ThunderstormAlert;
    }
    if (type == "fog"_L1) {
        return Weather::FogAlert;
    }
    if (type == "high-temperature"_L1) {
        return Weather::HighTemperatureAlert;
    }
    if (type == "low-temperature"_L1) {
        return Weather::LowTemperatureAlert;
    }
    if (type == "coastalevent"_L1) {
        return Weather::CoastalEventAlert;
    }
    if (type == "forest-fire"_L1) {
        return Weather::ForestFireAlert;
    }
    if (type == "avalanches"_L1) {
        return Weather::AvalanchesAlert;
    }
    if (type == "rain"_L1) {
        return Weather::RainAlert;
    }
    if (type == "flooding"_L1) {
        return Weather::FloodingAlert;
    }
    if (type == "rain-flood"_L1) {
        return Weather::RainFloodAlert;
    }

    return Weather::GenericAlert;
}

Weather::AlertSeverity Weather::alertSeverityFromString(const QString &severity)
{
    if (severity == "minor"_L1) {
        return Weather::MinorSeverity;
    }
    if (severity == "moderate"_L1) {
        return Weather::ModerateSeverity;
    }
    if (severity == "severe"_L1) {
        return Weather::SevereSeverity;
    }
    if (severity == "extreme"_L1) {
        return Weather::ExtremeSeverity;
    }

    throw std::runtime_error("undefined behaviour");
}

QString Weather::alertSeverityToString(AlertSeverity severity)
{
    switch (severity) {
    case MinorSeverity:
        return u"minor"_s;
    case ModerateSeverity:
        return u"moderate"_s;
    case SevereSeverity:
        return u"severe"_s;
    case ExtremeSeverity:
        return u"extreme"_s;
    }

    return {};
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Weather.cpp"
// NOLINTEND
