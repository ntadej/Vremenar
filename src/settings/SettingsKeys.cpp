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

#include "settings/Settings.h"

namespace Vremenar
{

// Country selection
const QString Settings::KEY_WEATHER_SOURCE = QStringLiteral("weather/source");

// Map startup settings
const QString Settings::KEY_STARTUP_MAP_ENABLED = QStringLiteral("map/startup");
const QString Settings::KEY_STARTUP_MAP_STYLE = QStringLiteral("map/style");
const QString Settings::KEY_STARTUP_MAP_TYPE = QStringLiteral("map/type");
const QString Settings::KEY_STARTUP_MAP_ZOOM_LEVEL = QStringLiteral("map/zoom-level");
const QString Settings::KEY_STARTUP_MAP_LATITUDE = QStringLiteral("map/latitude");
const QString Settings::KEY_STARTUP_MAP_LONGITUDE = QStringLiteral("map/longitude");

// Locale
const QString Settings::KEY_LOCALE = QStringLiteral("locale");

// GUI
const QString Settings::KEY_SHOW_IN_TRAY = QStringLiteral("gui/tray");
#if defined(Q_OS_MACOS)
const QString Settings::KEY_SHOW_IN_DOCK = QStringLiteral("gui/dock");
#endif

// GUI - start
const QString Settings::KEY_REMEMBER_POSITION = QStringLiteral("gui/remember-position");
const QString Settings::KEY_REMEMBER_SIZE = QStringLiteral("gui/remember-size");

const QString Settings::KEY_WIDTH = QStringLiteral("gui/width");
const QString Settings::KEY_HEIGHT = QStringLiteral("gui/height");
const QString Settings::KEY_POS_X = QStringLiteral("gui/posx");
const QString Settings::KEY_POS_Y = QStringLiteral("gui/posy");

} // namespace Vremenar
