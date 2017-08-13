/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "settings/Settings.h"

// Locale
const QString Settings::KEY_LOCALE = "locale";

// GUI
const QString Settings::KEY_SHOW_IN_TRAY = "gui/tray";
#if defined(Q_OS_MACOS)
const QString Settings::KEY_SHOW_IN_DOCK = "gui/dock";
#endif

// GUI - start
const QString Settings::KEY_REMEMBER_POSITION = "gui/remember-position";
const QString Settings::KEY_REMEMBER_SIZE = "gui/remember-size";

const QString Settings::KEY_WIDTH = "gui/width";
const QString Settings::KEY_HEIGHT = "gui/height";
const QString Settings::KEY_POS_X = "gui/posx";
const QString Settings::KEY_POS_Y = "gui/posy";
