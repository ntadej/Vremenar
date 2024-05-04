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

#ifndef VREMENAR_WEATHER_H_
#define VREMENAR_WEATHER_H_

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <cstdint>

namespace Vremenar::Weather
{

Q_NAMESPACE

enum ObservationType : std::uint8_t {
    Historical,
    Recent,
    Forecast
};

enum MapStyle : std::uint8_t {
    UnknownMapStyle,
    SatelliteMapStyle,
    StreetsLightMapStyle,
    StreetsDarkMapStyle
};

enum MapType : std::uint8_t {
    UnknownMapType,
    WeatherConditionMap,
    PrecipitationMap,
    CloudCoverageMap,
    WindSpeedMap,
    TemperatureMap,
    HailProbabilityMap,
    UVIndexMaxMap,
    UVDoseMap,
};

enum MapRenderingType : std::uint8_t {
    ImageRendering,
    TilesRendering,
    IconsRendering,
    UnknownRendering,
};

enum AlertType : std::uint8_t {
    GenericAlert,
    WindAlert,
    SnowIceAlert,
    ThunderstormAlert,
    FogAlert,
    HighTemperatureAlert,
    LowTemperatureAlert,
    CoastalEventAlert,
    ForestFireAlert,
    AvalanchesAlert,
    RainAlert,
    FloodingAlert,
    RainFloodAlert,
};

enum AlertSeverity : std::uint8_t {
    MinorSeverity,
    ModerateSeverity,
    SevereSeverity,
    ExtremeSeverity
};

Q_ENUM_NS(ObservationType)
Q_ENUM_NS(MapStyle)
Q_ENUM_NS(MapType)
Q_ENUM_NS(MapRenderingType)
Q_ENUM_NS(AlertType)
Q_ENUM_NS(AlertSeverity)

QString dateDisplay(const QDateTime &time);
QString timeDisplay(const QDateTime &time);

ObservationType observationTypeFromString(const QString &type);

MapStyle mapStyleFromString(const QString &style);
QString mapStyleToString(Vremenar::Weather::MapStyle style);
Q_INVOKABLE QString mapStyleToLocalizedString(Vremenar::Weather::MapStyle style);

MapType mapTypeFromString(const QString &type);
QString mapTypeToString(Vremenar::Weather::MapType type);
Q_INVOKABLE QString mapTypeToLocalizedString(Vremenar::Weather::MapType type);

MapRenderingType mapRenderingTypeFromString(const QString &type);

AlertType alertTypeFromString(const QString &type);
AlertSeverity alertSeverityFromString(const QString &severity);
Q_INVOKABLE QString alertSeverityToString(Vremenar::Weather::AlertSeverity severity);

} // namespace Vremenar::Weather

#endif // VREMENAR_WEATHER_H_
