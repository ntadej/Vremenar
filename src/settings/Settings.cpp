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

#include "location/Location.h"
#include "weather/Sources.h"
#include "weather/Weather.h"

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>

namespace Vremenar
{

Settings::Settings(QObject *parent)
    : QSettings(parent),
      _weatherSource(DEFAULT_WEATHER_SOURCE),
      _weatherSourceInitialChoice(DEFAULT_WEATHER_SOURCE_INITIAL_CHOICE),
      _locationSource(DEFAULT_LOCATION_SOURCE),
      _locationInitialChoice(DEFAULT_LOCATION_INITIAL_CHOICE),
      _locationStation(DEFAULT_LOCATION_STATION),
      _locationLatitude(DEFAULT_LOCATION_LATITUDE),
      _locationLongitude(DEFAULT_LOCATION_LONGITUDE),
      _startupMapEnabled(DEFAULT_STARTUP_MAP_ENABLED),
      _startupMapStyle(DEFAULT_STARTUP_MAP_STYLE),
      _startupMapType(DEFAULT_STARTUP_MAP_TYPE),
      _startupMapZoomLevel(DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI),
      _startupMapLatitude(DEFAULT_STARTUP_MAP_LATITUDE_SI),
      _startupMapLongitude(DEFAULT_STARTUP_MAP_LONGITUDE_SI),
      _locale(DEFAULT_LOCALE),
      _notificationsEnabled(DEFAULT_NOTIFICATIONS_ENABLED),
      _notificationsInitialChoice(DEFAULT_NOTIFICATIONS_INITIAL_CHOICE),
      _notificationsAlertSeverity(DEFAULT_NOTIFICATIONS_ALERT_SEVERITY),
      _notificationsAlertKeys(DEFAULT_NOTIFICATIONS_ALERT_KEYS),
      _showInTray(DEFAULT_SHOW_IN_TRAY),
#if defined(Q_OS_MACOS)
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
    _map.insert(KEY_WEATHER_SOURCE_INITIAL_CHOICE, DEFAULT_WEATHER_SOURCE_INITIAL_CHOICE);
    _map.insert(KEY_LOCATION_SOURCE, DEFAULT_LOCATION_SOURCE);
    _map.insert(KEY_LOCATION_INITIAL_CHOICE, DEFAULT_LOCATION_INITIAL_CHOICE);
    _map.insert(KEY_LOCATION_STATION, DEFAULT_LOCATION_STATION);
    _map.insert(KEY_LOCATION_LATITUDE, DEFAULT_LOCATION_LATITUDE);
    _map.insert(KEY_LOCATION_LONGITUDE, DEFAULT_LOCATION_LONGITUDE);
    _map.insert(KEY_STARTUP_MAP_ENABLED, DEFAULT_STARTUP_MAP_ENABLED);
    _map.insert(KEY_STARTUP_MAP_STYLE, DEFAULT_STARTUP_MAP_STYLE);
    _map.insert(KEY_STARTUP_MAP_TYPE, DEFAULT_STARTUP_MAP_TYPE);
    _map.insert(KEY_STARTUP_MAP_ZOOM_LEVEL, DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI);
    _map.insert(KEY_STARTUP_MAP_LATITUDE, DEFAULT_STARTUP_MAP_LATITUDE_SI);
    _map.insert(KEY_STARTUP_MAP_LONGITUDE, DEFAULT_STARTUP_MAP_LONGITUDE_SI);
    _map.insert(KEY_LOCALE, DEFAULT_LOCALE);
    _map.insert(KEY_NOTIFICATIONS_ENABLED, DEFAULT_NOTIFICATIONS_ENABLED);
    _map.insert(KEY_NOTIFICATIONS_INITIAL_CHOICE, DEFAULT_NOTIFICATIONS_INITIAL_CHOICE);
    _map.insert(KEY_NOTIFICATIONS_ALERT_SEVERITY, DEFAULT_NOTIFICATIONS_ALERT_SEVERITY);
    _map.insert(KEY_NOTIFICATIONS_ALERT_KEYS, DEFAULT_NOTIFICATIONS_ALERT_KEYS);
    _map.insert(KEY_SHOW_IN_TRAY, DEFAULT_SHOW_IN_TRAY);
#if defined(Q_OS_MACOS)
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
    setValue(KEY_WEATHER_SOURCE_INITIAL_CHOICE, weatherSourceInitialChoice());

    setValue(KEY_LOCATION_SOURCE, static_cast<int>(locationSource()));
    setValue(KEY_LOCATION_INITIAL_CHOICE, locationInitialChoice());
    setValue(KEY_LOCATION_STATION, locationStation());
    setValue(KEY_LOCATION_LATITUDE, locationLatitude());
    setValue(KEY_LOCATION_LONGITUDE, locationLongitude());

    setValue(KEY_STARTUP_MAP_ENABLED, startupMapEnabled());
    setValue(KEY_STARTUP_MAP_STYLE, static_cast<int>(startupMapStyle()));
    setValue(KEY_STARTUP_MAP_TYPE, static_cast<int>(startupMapType()));
    setValue(KEY_STARTUP_MAP_ZOOM_LEVEL, startupMapZoomLevel());
    setValue(KEY_STARTUP_MAP_LATITUDE, startupMapLatitude());
    setValue(KEY_STARTUP_MAP_LONGITUDE, startupMapLongitude());

    setValue(KEY_LOCALE, locale());

    setValue(KEY_NOTIFICATIONS_ENABLED, notificationsEnabled());
    setValue(KEY_NOTIFICATIONS_INITIAL_CHOICE, notificationsInitialChoice());
    setValue(KEY_NOTIFICATIONS_ALERT_SEVERITY, notificationsAlertSeverity());
    setValue(KEY_NOTIFICATIONS_ALERT_KEYS, notificationsAlertKeys());

    setValue(KEY_SHOW_IN_TRAY, showInTray());
#if defined(Q_OS_MACOS)
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
    setWeatherSource(static_cast<Sources::Country>(value(KEY_WEATHER_SOURCE, defaultValue(KEY_WEATHER_SOURCE)).toInt()));
    setWeatherSourceInitialChoice(value(KEY_WEATHER_SOURCE_INITIAL_CHOICE, defaultValue(KEY_WEATHER_SOURCE_INITIAL_CHOICE)).toBool());

    setLocationSource(static_cast<Location::Source>(value(KEY_LOCATION_SOURCE, defaultValue(KEY_LOCATION_SOURCE)).toInt()));
    setLocationInitialChoice(value(KEY_LOCATION_INITIAL_CHOICE, defaultValue(KEY_LOCATION_INITIAL_CHOICE)).toBool());
    setLocationStation(value(KEY_LOCATION_STATION, defaultValue(KEY_LOCATION_STATION)).toString());
    setLocationLatitude(value(KEY_LOCATION_LATITUDE, defaultValue(KEY_LOCATION_LATITUDE)).toDouble());
    setLocationLongitude(value(KEY_LOCATION_LONGITUDE, defaultValue(KEY_LOCATION_LONGITUDE)).toDouble());

    setStartupMapEnabled(value(KEY_STARTUP_MAP_ENABLED, defaultValue(KEY_STARTUP_MAP_ENABLED)).toBool());
    setStartupMapStyle(static_cast<Weather::MapStyle>(value(KEY_STARTUP_MAP_STYLE, defaultValue(KEY_STARTUP_MAP_STYLE)).toInt()));
    setStartupMapType(static_cast<Weather::MapType>(value(KEY_STARTUP_MAP_TYPE, defaultValue(KEY_STARTUP_MAP_TYPE)).toInt()));
    setStartupMapZoomLevel(value(KEY_STARTUP_MAP_ZOOM_LEVEL, defaultValue(KEY_STARTUP_MAP_ZOOM_LEVEL)).toReal());
    setStartupMapLatitude(value(KEY_STARTUP_MAP_LATITUDE, defaultValue(KEY_STARTUP_MAP_LATITUDE)).toDouble());
    setStartupMapLongitude(value(KEY_STARTUP_MAP_LONGITUDE, defaultValue(KEY_STARTUP_MAP_LONGITUDE)).toDouble());

    setLocale(value(KEY_LOCALE, defaultValue(KEY_LOCALE)).toString());

    setNotificationsEnabled(value(KEY_NOTIFICATIONS_ENABLED, defaultValue(KEY_NOTIFICATIONS_ENABLED)).toBool());
    setNotificationsInitialChoice(value(KEY_NOTIFICATIONS_INITIAL_CHOICE, defaultValue(KEY_NOTIFICATIONS_INITIAL_CHOICE)).toBool());
    setNotificationsAlertSeverity(static_cast<Weather::AlertSeverity>(value(KEY_NOTIFICATIONS_ALERT_SEVERITY, defaultValue(KEY_NOTIFICATIONS_ALERT_SEVERITY)).toInt()));
    setNotificationsAlertKeys(value(KEY_NOTIFICATIONS_ALERT_KEYS, defaultValue(KEY_NOTIFICATIONS_ALERT_KEYS)).toStringList());

    setShowInTray(value(KEY_SHOW_IN_TRAY, defaultValue(KEY_SHOW_IN_TRAY)).toBool());
#if defined(Q_OS_MACOS)
    setShowInDock(value(KEY_SHOW_IN_DOCK, defaultValue(KEY_SHOW_IN_DOCK)).toBool());
#endif

    setRememberPosition(value(KEY_REMEMBER_POSITION, defaultValue(KEY_REMEMBER_POSITION)).toBool());
    setRememberSize(value(KEY_REMEMBER_SIZE, defaultValue(KEY_REMEMBER_SIZE)).toBool());
    setWidth(value(KEY_WIDTH, defaultValue(KEY_WIDTH)).toInt());
    setHeight(value(KEY_HEIGHT, defaultValue(KEY_HEIGHT)).toInt());
    setPosX(value(KEY_POS_X, defaultValue(KEY_POS_X)).toInt());
    setPosY(value(KEY_POS_Y, defaultValue(KEY_POS_Y)).toInt());

    setUuid(value(KEY_UUID, defaultValue(KEY_UUID)).toString());

    emit settingsReloaded();
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

int Settings::startupLocationSetting() const
{
    return locationSource() == Location::Disabled ? 1 : 0;
}

int Settings::startupNotificationsSetting() const
{
    if (notificationsEnabled()) {
        return notificationsAlertSeverity();
    }

    return Weather::ExtremeSeverity + 1;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Settings.cpp"
// NOLINTEND
