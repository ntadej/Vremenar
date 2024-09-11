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

#include "common/containers/Hyperlink.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <memory>
#include <stdexcept>
#include <vector>

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

Weather::Source Weather::sourceFromString(const QString &source)
{
    if (source == "si"_L1) {
        return Slovenia;
    }
    if (source == "de"_L1) {
        return Germany;
    }
    if (source == "global"_L1) {
        return Global;
    }

    throw std::runtime_error("unknown source");
}

QString Weather::sourceToString(Source source)
{
    switch (source) {
    case Slovenia:
        return u"si"_s;
    case Germany:
        return u"de"_s;
    case Global:
        return u"global"_s;
    }

    throw std::runtime_error("unknown source");
}

QString Weather::sourceToLocalizedString(Source source)
{
    switch (source) {
    case Slovenia:
        return "ARSO (%1)"_L1.arg(QObject::tr("Slovenia"));
    case Germany:
        return "DWD (%1)"_L1.arg(QObject::tr("Germany"));
    case Global:
        return QObject::tr("Global");
    }

    return {};
}

Weather::ObservationType Weather::observationTypeFromString(const QString &type)
{
    if (type == "historical"_L1) {
        return Historical;
    }
    if (type == "forecast"_L1) {
        return Forecast;
    }

    return Recent;
}

Weather::MapStyle Weather::mapStyleFromString(const QString &style)
{
    if (style == "satellite"_L1) {
        return SatelliteMapStyle;
    }
    if (style == "streets-light"_L1) {
        return StreetsLightMapStyle;
    }
    if (style == "streets-dark"_L1) {
        return StreetsDarkMapStyle;
    }

    return UnknownMapStyle;
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
        return WeatherConditionMap;
    }
    if (type == "precipitation"_L1) {
        return PrecipitationMap;
    }
    if (type == "precipitation_global"_L1) {
        return PrecipitationGlobalMap;
    }
    if (type == "cloud"_L1) {
        return CloudCoverageMap;
    }
    if (type == "cloud_infrared_global"_L1) {
        return CloudCoverageInfraredGlobalMap;
    }
    if (type == "wind"_L1) {
        return WindSpeedMap;
    }
    if (type == "temperature"_L1) {
        return TemperatureMap;
    }
    if (type == "hail"_L1) {
        return HailProbabilityMap;
    }
    if (type == "uv_index_max"_L1) {
        return UVIndexMaxMap;
    }
    if (type == "uv_dose"_L1) {
        return UVDoseMap;
    }

    return UnknownMapType;
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

QString Weather::mapTypeToLocalizedString(MapType type,
                                          Source source)
{
    switch (type) {
    case WeatherConditionMap:
        return QObject::tr("Weather condition");
    case PrecipitationMap:
        return QObject::tr("Precipitation");
    case PrecipitationGlobalMap:
        if (source == Germany) {
            return QObject::tr("Precipitation (global)");
        }
        if (source == Slovenia) {
            return QObject::tr("Precipitation with forecast");
        }
        return QObject::tr("Precipitation");
    case CloudCoverageMap:
        return QObject::tr("Cloud coverage");
    case CloudCoverageInfraredGlobalMap:
        if (source == Slovenia) {
            return QObject::tr("Cloud coverage (satellite)");
        }
        return QObject::tr("Cloud coverage");
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
        return ImageRendering;
    }
    if (type == "tiles"_L1) {
        return TilesRendering;
    }
    if (type == "icons"_L1) {
        return IconsRendering;
    }

    return UnknownRendering;
}

Weather::AlertType Weather::alertTypeFromString(const QString &type)
{
    if (type == "wind"_L1) {
        return WindAlert;
    }
    if (type == "snow-ice"_L1) {
        return SnowIceAlert;
    }
    if (type == "thunderstorm"_L1) {
        return ThunderstormAlert;
    }
    if (type == "fog"_L1) {
        return FogAlert;
    }
    if (type == "high-temperature"_L1) {
        return HighTemperatureAlert;
    }
    if (type == "low-temperature"_L1) {
        return LowTemperatureAlert;
    }
    if (type == "coastalevent"_L1) {
        return CoastalEventAlert;
    }
    if (type == "forest-fire"_L1) {
        return ForestFireAlert;
    }
    if (type == "avalanches"_L1) {
        return AvalanchesAlert;
    }
    if (type == "rain"_L1) {
        return RainAlert;
    }
    if (type == "flooding"_L1) {
        return FloodingAlert;
    }
    if (type == "rain-flood"_L1) {
        return RainFloodAlert;
    }

    return GenericAlert;
}

Weather::AlertSeverity Weather::alertSeverityFromString(const QString &severity)
{
    if (severity == "minor"_L1) {
        return MinorSeverity;
    }
    if (severity == "moderate"_L1) {
        return ModerateSeverity;
    }
    if (severity == "severe"_L1) {
        return SevereSeverity;
    }
    if (severity == "extreme"_L1) {
        return ExtremeSeverity;
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

std::vector<std::unique_ptr<Hyperlink>> Weather::copyright(Source source,
                                                           MapType mapType)
{
    std::vector<std::unique_ptr<Hyperlink>> links;

    switch (source) {
    case Slovenia:
        links.emplace_back(std::make_unique<Hyperlink>(
            u"© "_s + QObject::tr("Slovenian Environment Agency"),
            u"https://www.arso.gov.si"_s));
        break;
    case Germany:
        links.emplace_back(std::make_unique<Hyperlink>(
            u"© Deutscher Wetterdienst"_s,
            u"https://dwd.de"_s));
        break;
    case Global:
        links.emplace_back(std::make_unique<Hyperlink>(
            u"© "_s + QObject::tr("RainViewer"),
            u"https://rainviewer.com"_s));
    }

    if (source != Global
        && (mapType == PrecipitationGlobalMap || mapType == CloudCoverageInfraredGlobalMap)) {
        links.emplace_back(std::make_unique<Hyperlink>(
            u"© "_s + QObject::tr("RainViewer"),
            u"https://rainviewer.com"_s));
    }

    return links;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Weather.cpp"
// NOLINTEND
