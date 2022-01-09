/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "settings/Settings.h"

namespace Vremenar
{

// Country selection
const Sources::Country Settings::DEFAULT_WEATHER_SOURCE = Sources::Slovenia;
const bool Settings::DEFAULT_INITIAL_WEATHER_SOURCE_CHOSEN = false;

// Location
const Location::Source Settings::DEFAULT_LOCATION_SOURCE = Location::Automatic;
const QString Settings::DEFAULT_LOCATION_STATION = QString();
const double Settings::DEFAULT_LOCATION_LATITUDE = 0.;
const double Settings::DEFAULT_LOCATION_LONGITUDE = 0.;

// Map startup settings
const bool Settings::DEFAULT_STARTUP_MAP_ENABLED = true;
const Weather::MapStyle Settings::DEFAULT_STARTUP_MAP_STYLE = Weather::SatelliteMapStyle;
const Weather::MapType Settings::DEFAULT_STARTUP_MAP_TYPE = Weather::WeatherConditionMap;

const qreal Settings::DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI = 8;
const qreal Settings::DEFAULT_STARTUP_MAP_ZOOM_LEVEL_DE = 7.5;

const double Settings::DEFAULT_STARTUP_MAP_LATITUDE_SI = 46.119944;
const double Settings::DEFAULT_STARTUP_MAP_LONGITUDE_SI = 14.815333;
const double Settings::DEFAULT_STARTUP_MAP_LATITUDE_DE = 52.3759;
const double Settings::DEFAULT_STARTUP_MAP_LONGITUDE_DE = 10.447683;

const double Settings::DEFAULT_MIN_MAP_LATITUDE_SI = 44.6;
const double Settings::DEFAULT_MAX_MAP_LATITUDE_SI = 47.5;
const double Settings::DEFAULT_MIN_MAP_LONGITUDE_SI = 12.;
const double Settings::DEFAULT_MAX_MAP_LONGITUDE_SI = 17.5;
const double Settings::DEFAULT_MIN_MAP_LATITUDE_DE = 47.;
const double Settings::DEFAULT_MAX_MAP_LATITUDE_DE = 55.3;
const double Settings::DEFAULT_MIN_MAP_LONGITUDE_DE = 5.7;
const double Settings::DEFAULT_MAX_MAP_LONGITUDE_DE = 15.3;

// Locale
const QString Settings::DEFAULT_LOCALE = {};

// GUI
#if defined(Q_OS_MACOS)
const bool Settings::DEFAULT_SHOW_IN_TRAY = true;
const bool Settings::DEFAULT_SHOW_IN_DOCK = true;
#else
const bool Settings::DEFAULT_SHOW_IN_TRAY = false;
#endif

// GUI - start
const bool Settings::DEFAULT_REMEMBER_POSITION = false;
const bool Settings::DEFAULT_REMEMBER_SIZE = false;

const int Settings::DEFAULT_WIDTH = 650;
const int Settings::DEFAULT_HEIGHT = 300;
const int Settings::DEFAULT_POS_X = 0;
const int Settings::DEFAULT_POS_Y = 0;

// Special
const QString Settings::DEFAULT_UUID = QString();

} // namespace Vremenar
