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

#include "settings/Settings.h"

namespace Vremenar
{

// Map startup settings
const bool Settings::DEFAULT_STARTUP_MAP_ENABLED = true;
const Weather::MapType Settings::DEFAULT_STARTUP_MAP_TYPE = Weather::ForecastMap;
const qreal Settings::DEFAULT_STARTUP_MAP_ZOOM_LEVEL = 8;
const double Settings::DEFAULT_STARTUP_MAP_LATITUDE = 46.119944;
const double Settings::DEFAULT_STARTUP_MAP_LONGITUDE = 14.815333;

// Locale
const QString Settings::DEFAULT_LOCALE = {};

// GUI
const bool Settings::DEFAULT_SHOW_IN_TRAY = false;
#if defined(Q_OS_MACOS)
const bool Settings::DEFAULT_SHOW_IN_DOCK = true;
#endif

// GUI - start
const bool Settings::DEFAULT_REMEMBER_POSITION = false;
const bool Settings::DEFAULT_REMEMBER_SIZE = false;

const int Settings::DEFAULT_WIDTH = 650;
const int Settings::DEFAULT_HEIGHT = 300;
const int Settings::DEFAULT_POS_X = 0;
const int Settings::DEFAULT_POS_Y = 0;

} // namespace Vremenar
