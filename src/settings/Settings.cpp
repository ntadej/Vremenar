/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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

Settings::Settings(QObject *parent)
    : QSettings(parent),
      _weatherSource(DEFAULT_WEATHER_SOURCE),
      _initialWeatherSourceChosen(DEFAULT_INITIAL_WEATHER_SOURCE_CHOSEN),
      _startupMapEnabled(DEFAULT_STARTUP_MAP_ENABLED),
      _startupMapStyle(DEFAULT_STARTUP_MAP_STYLE),
      _startupMapType(DEFAULT_STARTUP_MAP_TYPE),
      _startupMapZoomLevel(DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI),
      _startupMapLatitude(DEFAULT_STARTUP_MAP_LATITUDE_SI),
      _startupMapLongitude(DEFAULT_STARTUP_MAP_LONGITUDE_SI),
      _locale(DEFAULT_LOCALE),
#if defined(Q_OS_MACOS)
      _showInTray(DEFAULT_SHOW_IN_TRAY),
      _showInDock(DEFAULT_SHOW_IN_DOCK),
#endif
      _rememberPosition(DEFAULT_REMEMBER_POSITION),
      _rememberSize(DEFAULT_REMEMBER_SIZE),
      _width(DEFAULT_WIDTH),
      _height(DEFAULT_HEIGHT),
      _posX(DEFAULT_POS_X),
      _posY(DEFAULT_POS_Y),
      _uuid(DEFAULT_UUID)
{
    _map.insert(KEY_WEATHER_SOURCE, DEFAULT_WEATHER_SOURCE);
    _map.insert(KEY_INITIAL_WEATHER_SOURCE_CHOSEN, DEFAULT_INITIAL_WEATHER_SOURCE_CHOSEN);
    _map.insert(KEY_STARTUP_MAP_ENABLED, DEFAULT_STARTUP_MAP_ENABLED);
    _map.insert(KEY_STARTUP_MAP_STYLE, DEFAULT_STARTUP_MAP_STYLE);
    _map.insert(KEY_STARTUP_MAP_TYPE, DEFAULT_STARTUP_MAP_TYPE);
    _map.insert(KEY_STARTUP_MAP_ZOOM_LEVEL, DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI);
    _map.insert(KEY_STARTUP_MAP_LATITUDE, DEFAULT_STARTUP_MAP_LATITUDE_SI);
    _map.insert(KEY_STARTUP_MAP_LONGITUDE, DEFAULT_STARTUP_MAP_LONGITUDE_SI);
    _map.insert(KEY_LOCALE, DEFAULT_LOCALE);
#if defined(Q_OS_MACOS)
    _map.insert(KEY_SHOW_IN_TRAY, DEFAULT_SHOW_IN_TRAY);
    _map.insert(KEY_SHOW_IN_DOCK, DEFAULT_SHOW_IN_DOCK);
#endif
    _map.insert(KEY_REMEMBER_POSITION, DEFAULT_REMEMBER_POSITION);
    _map.insert(KEY_REMEMBER_SIZE, DEFAULT_REMEMBER_SIZE);
    _map.insert(KEY_WIDTH, DEFAULT_WIDTH);
    _map.insert(KEY_HEIGHT, DEFAULT_HEIGHT);
    _map.insert(KEY_POS_X, DEFAULT_POS_X);
    _map.insert(KEY_POS_Y, DEFAULT_POS_Y);
    _map.insert(KEY_UUID, DEFAULT_UUID);

    readSettings();
}

void Settings::writeSettings()
{
    setValue(KEY_WEATHER_SOURCE, static_cast<int>(weatherSource()));
    setValue(KEY_INITIAL_WEATHER_SOURCE_CHOSEN, initialWeatherSourceChosen());

    setValue(KEY_STARTUP_MAP_ENABLED, startupMapEnabled());
    setValue(KEY_STARTUP_MAP_STYLE, static_cast<int>(startupMapStyle()));
    setValue(KEY_STARTUP_MAP_TYPE, static_cast<int>(startupMapType()));
    setValue(KEY_STARTUP_MAP_ZOOM_LEVEL, startupMapZoomLevel());
    setValue(KEY_STARTUP_MAP_LATITUDE, startupMapLatitude());
    setValue(KEY_STARTUP_MAP_LONGITUDE, startupMapLongitude());

    setValue(KEY_LOCALE, locale());

#if defined(Q_OS_MACOS)
    setValue(KEY_SHOW_IN_TRAY, showInTray());
    setValue(KEY_SHOW_IN_DOCK, showInDock());
#endif

    setValue(KEY_REMEMBER_POSITION, rememberPosition());
    setValue(KEY_REMEMBER_SIZE, rememberSize());
    setValue(KEY_WIDTH, width());
    setValue(KEY_HEIGHT, height());
    setValue(KEY_POS_X, posX());
    setValue(KEY_POS_Y, posY());

    setValue(KEY_UUID, uuid());

    sync();
}

void Settings::readSettings()
{
    setWeatherSource(Sources::Country(value(KEY_WEATHER_SOURCE, defaultValue(KEY_WEATHER_SOURCE)).toInt()));
    setInitialWeatherSourceChosen(value(KEY_INITIAL_WEATHER_SOURCE_CHOSEN, defaultValue(KEY_INITIAL_WEATHER_SOURCE_CHOSEN)).toBool());

    setStartupMapEnabled(value(KEY_STARTUP_MAP_ENABLED, defaultValue(KEY_STARTUP_MAP_ENABLED)).toBool());
    setStartupMapStyle(Weather::MapStyle(value(KEY_STARTUP_MAP_STYLE, defaultValue(KEY_STARTUP_MAP_STYLE)).toInt()));
    setStartupMapType(Weather::MapType(value(KEY_STARTUP_MAP_TYPE, defaultValue(KEY_STARTUP_MAP_TYPE)).toInt()));
    setStartupMapZoomLevel(value(KEY_STARTUP_MAP_ZOOM_LEVEL, defaultValue(KEY_STARTUP_MAP_ZOOM_LEVEL)).toReal());
    setStartupMapLatitude(value(KEY_STARTUP_MAP_LATITUDE, defaultValue(KEY_STARTUP_MAP_LATITUDE)).toDouble());
    setStartupMapLongitude(value(KEY_STARTUP_MAP_LONGITUDE, defaultValue(KEY_STARTUP_MAP_LONGITUDE)).toDouble());

    setLocale(value(KEY_LOCALE, defaultValue(KEY_LOCALE)).toString());

#if defined(Q_OS_MACOS)
    setShowInTray(value(KEY_SHOW_IN_TRAY, defaultValue(KEY_SHOW_IN_TRAY)).toBool());
    setShowInDock(value(KEY_SHOW_IN_DOCK, defaultValue(KEY_SHOW_IN_DOCK)).toBool());
#endif

    setRememberPosition(value(KEY_REMEMBER_POSITION, defaultValue(KEY_REMEMBER_POSITION)).toBool());
    setRememberSize(value(KEY_REMEMBER_SIZE, defaultValue(KEY_REMEMBER_SIZE)).toBool());
    setWidth(value(KEY_WIDTH, defaultValue(KEY_WIDTH)).toInt());
    setHeight(value(KEY_HEIGHT, defaultValue(KEY_HEIGHT)).toInt());
    setPosX(value(KEY_POS_X, defaultValue(KEY_POS_X)).toInt());
    setPosY(value(KEY_POS_Y, defaultValue(KEY_POS_Y)).toInt());

    setUuid(value(KEY_UUID, defaultValue(KEY_UUID)).toString());

    Q_EMIT settingsReloaded();
}

QVariant Settings::defaultValue(const QString &key) const
{
    return _map.value(key);
}

void Settings::resetStartupMapCoordinates()
{
    setStartupMapType(Weather::WeatherConditionMap);

    if (weatherSource() == Sources::Germany) {
        setStartupMapZoomLevel(DEFAULT_STARTUP_MAP_ZOOM_LEVEL_DE);
        setStartupMapLatitude(DEFAULT_STARTUP_MAP_LATITUDE_DE);
        setStartupMapLongitude(DEFAULT_STARTUP_MAP_LONGITUDE_DE);
    } else {
        setStartupMapZoomLevel(DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI);
        setStartupMapLatitude(DEFAULT_STARTUP_MAP_LATITUDE_SI);
        setStartupMapLongitude(DEFAULT_STARTUP_MAP_LONGITUDE_SI);
    }
}

} // namespace Vremenar
