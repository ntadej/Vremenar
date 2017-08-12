/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "settings/Settings.h"

Settings::Settings(QObject *parent)
    : QSettings(parent)
{
    _map[KEY_LOCALE] = DEFAULT_LOCALE;
    _map[KEY_WIDTH] = DEFAULT_WIDTH;
    _map[KEY_HEIGHT] = DEFAULT_HEIGHT;
    _map[KEY_POS_X] = DEFAULT_POS_X;
    _map[KEY_POS_Y] = DEFAULT_POS_Y;

    readSettings();
}

Settings::~Settings() {}

void Settings::writeSettings()
{
    setValue(KEY_LOCALE, locale());

    setValue(KEY_WIDTH, width());
    setValue(KEY_HEIGHT, height());
    setValue(KEY_POS_X, posX());
    setValue(KEY_POS_Y, posY());

    sync();
}

void Settings::readSettings()
{
    setLocale(value(KEY_LOCALE, defaultValue(KEY_LOCALE)).toString());

    setWidth(value(KEY_WIDTH, defaultValue(KEY_WIDTH)).toInt());
    setHeight(value(KEY_HEIGHT, defaultValue(KEY_HEIGHT)).toInt());
    setPosX(value(KEY_POS_X, defaultValue(KEY_POS_X)).toInt());
    setPosY(value(KEY_POS_Y, defaultValue(KEY_POS_Y)).toInt());
}

QVariant Settings::defaultValue(const QString &key) const
{
    return _map.value(key);
}
