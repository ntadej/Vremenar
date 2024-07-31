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

#include "settings/Settings.h"

#include <QtCore/QString>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

// Country selection
const QString Settings::KEY_WEATHER_SOURCE = u"weather/source"_s;
const QString Settings::KEY_WEATHER_SOURCE_INITIAL_CHOICE = u"weather/initial-source-chosen"_s;

// Location
const QString Settings::KEY_LOCATION_SOURCE = u"location/source"_s;
const QString Settings::KEY_LOCATION_INITIAL_CHOICE = u"location/initial-choice"_s;
const QString Settings::KEY_LOCATION_STATION = u"location/station"_s;
const QString Settings::KEY_LOCATION_LATITUDE = u"location/latitude"_s;
const QString Settings::KEY_LOCATION_LONGITUDE = u"location/longitude"_s;

// Map startup settings
const QString Settings::KEY_STARTUP_MAP_ENABLED = u"map/startup"_s;
const QString Settings::KEY_STARTUP_MAP_STYLE = u"map/style"_s;
const QString Settings::KEY_STARTUP_MAP_TYPE = u"map/type"_s;
const QString Settings::KEY_STARTUP_MAP_ZOOM_LEVEL = u"map/zoom-level"_s;
const QString Settings::KEY_STARTUP_MAP_LATITUDE = u"map/latitude"_s;
const QString Settings::KEY_STARTUP_MAP_LONGITUDE = u"map/longitude"_s;

// Locale
const QString Settings::KEY_LOCALE = u"locale"_s;

// Notifications
const QString Settings::KEY_NOTIFICATIONS_ENABLED = u"notifications/enabled"_s;
const QString Settings::KEY_NOTIFICATIONS_INITIAL_CHOICE = u"notifications/initial-choice"_s;
const QString Settings::KEY_NOTIFICATIONS_ALERT_SEVERITY = u"notifications/alert-severity"_s;
const QString Settings::KEY_NOTIFICATIONS_ALERT_KEYS = u"notifications/alert-keys"_s;

// GUI
const QString Settings::KEY_SHOW_IN_TRAY = u"gui/tray"_s;
#if defined(Q_OS_MACOS)
const QString Settings::KEY_SHOW_IN_DOCK = u"gui/dock"_s;
#endif

// GUI - start
const QString Settings::KEY_REMEMBER_POSITION = u"gui/remember-position"_s;
const QString Settings::KEY_REMEMBER_SIZE = u"gui/remember-size"_s;

const QString Settings::KEY_WIDTH = u"gui/width"_s;
const QString Settings::KEY_HEIGHT = u"gui/height"_s;
const QString Settings::KEY_POS_X = u"gui/posx"_s;
const QString Settings::KEY_POS_Y = u"gui/posy"_s;

// Special
const QString Settings::KEY_UUID = u"uuid"_s;

} // namespace Vremenar
