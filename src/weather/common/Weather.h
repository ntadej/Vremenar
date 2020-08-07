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

#ifndef VREMENAR_WEATHER_H_
#define VREMENAR_WEATHER_H_

#include <QtCore/QObject>

#include "common/Helpers.h"

namespace Vremenar::Weather
{

Q_NAMESPACE

enum ObservationType {
    Historical,
    Recent,
    Forecast
};

enum MapType {
    UnknownMap,
    WeatherConditionMap,
    PrecipitationMap,
    CloudCoverageMap,
    WindSpeedMap,
    TemperatureMap,
    HailProbabilityMap
};

enum MapRenderingType {
    ImageRendering,
    TilesRendering
};

Q_ENUM_NS(ObservationType)
Q_ENUM_NS(MapType)
Q_ENUM_NS(MapRenderingType)

ObservationType observationTypeFromString(const QString &type);

MapType mapTypeFromString(const QString &type);
QString mapTypeToString(Vremenar::Weather::MapType type);
Q_INVOKABLE QString mapTypeToLocalizedString(Vremenar::Weather::MapType type);

MapRenderingType mapRenderingTypeFromString(const QString &type);

constexpr CString blankPng{"iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNkYAAAAAYAAjCB0C8AAAAASUVORK5CYII="};

} // namespace Vremenar::Weather

#endif // VREMENAR_WEATHER_H_
