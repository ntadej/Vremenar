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

#ifndef VREMENAR_SETTINGS_H_
#define VREMENAR_SETTINGS_H_

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

class Settings : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(Vremenar::Sources::Country weatherSource READ weatherSource CONSTANT)
    Q_PROPERTY(bool weatherSourceInitialChoice READ weatherSourceInitialChoice CONSTANT)
    Q_PROPERTY(bool locationInitialChoice READ locationInitialChoice CONSTANT)
    Q_PROPERTY(bool notificationsInitialChoice READ notificationsInitialChoice CONSTANT)
    Q_PROPERTY(int startupLocationSetting READ startupLocationSetting CONSTANT)
    Q_PROPERTY(int startupNotificationsSetting READ startupNotificationsSetting CONSTANT)
    Q_PROPERTY(bool startupMapEnabled READ startupMapEnabled CONSTANT)
    Q_PROPERTY(qreal startupMapZoomLevel READ startupMapZoomLevel CONSTANT)
    Q_PROPERTY(bool rememberPosition READ rememberPosition CONSTANT)
    Q_PROPERTY(bool rememberSize READ rememberSize CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)
    Q_PROPERTY(int posX READ posX CONSTANT)
    Q_PROPERTY(int posY READ posY CONSTANT)
#if defined(Q_OS_MACOS)
    Q_PROPERTY(bool showInDock READ showInDock CONSTANT)
#endif

public:
    explicit Settings(QObject *parent = nullptr);

    Q_INVOKABLE void readSettings();
    void writeSettings();

    Q_INVOKABLE [[nodiscard]] QVariant defaultValue(const QString &key) const;

    // Country selection
    [[nodiscard]] Sources::Country weatherSource() const { return _weatherSource; }
    void setWeatherSource(Sources::Country s) { _weatherSource = s; }
    static const QString KEY_WEATHER_SOURCE;
    static const Sources::Country DEFAULT_WEATHER_SOURCE;

    [[nodiscard]] bool weatherSourceInitialChoice() const { return _weatherSourceInitialChoice; }
    void setWeatherSourceInitialChoice(bool b) { _weatherSourceInitialChoice = b; }
    static const QString KEY_WEATHER_SOURCE_INITIAL_CHOICE;
    static const bool DEFAULT_WEATHER_SOURCE_INITIAL_CHOICE;

    // Location
    [[nodiscard]] int startupLocationSetting() const;

    [[nodiscard]] Location::Source locationSource() const { return _locationSource; }
    void setLocationSource(Location::Source s) { _locationSource = s; }
    static const QString KEY_LOCATION_SOURCE;
    static const Location::Source DEFAULT_LOCATION_SOURCE;

    [[nodiscard]] bool locationInitialChoice() const { return _locationInitialChoice; }
    void setLocationInitialChoice(bool b) { _locationInitialChoice = b; }
    static const QString KEY_LOCATION_INITIAL_CHOICE;
    static const bool DEFAULT_LOCATION_INITIAL_CHOICE;

    [[nodiscard]] const QString &locationStation() const { return _locationStation; }
    void setLocationStation(const QString &s) { _locationStation = s; }
    static const QString KEY_LOCATION_STATION;
    static const QString DEFAULT_LOCATION_STATION;

    [[nodiscard]] double locationLatitude() const { return _locationLatitude; }
    void setLocationLatitude(double d) { _locationLatitude = d; }
    static const QString KEY_LOCATION_LATITUDE;
    static const double DEFAULT_LOCATION_LATITUDE;

    [[nodiscard]] double locationLongitude() const { return _locationLongitude; }
    void setLocationLongitude(double d) { _locationLongitude = d; }
    static const QString KEY_LOCATION_LONGITUDE;
    static const double DEFAULT_LOCATION_LONGITUDE;

    // Map startup settings
    [[nodiscard]] bool startupMapEnabled() const { return _startupMapEnabled; }
    void setStartupMapEnabled(bool b) { _startupMapEnabled = b; }
    static const QString KEY_STARTUP_MAP_ENABLED;
    static const bool DEFAULT_STARTUP_MAP_ENABLED;

    [[nodiscard]] Weather::MapStyle startupMapStyle() const { return _startupMapStyle; }
    void setStartupMapStyle(Weather::MapStyle s) { _startupMapStyle = s; }
    static const QString KEY_STARTUP_MAP_STYLE;
    static const Weather::MapStyle DEFAULT_STARTUP_MAP_STYLE;

    [[nodiscard]] Weather::MapType startupMapType() const { return _startupMapType; }
    void setStartupMapType(Weather::MapType t) { _startupMapType = t; }
    static const QString KEY_STARTUP_MAP_TYPE;
    static const Weather::MapType DEFAULT_STARTUP_MAP_TYPE;

    [[nodiscard]] qreal startupMapZoomLevel() const { return _startupMapZoomLevel; }
    void setStartupMapZoomLevel(qreal r) { _startupMapZoomLevel = r; }
    static const QString KEY_STARTUP_MAP_ZOOM_LEVEL;
    static const qreal DEFAULT_STARTUP_MAP_ZOOM_LEVEL_SI;
    static const qreal DEFAULT_STARTUP_MAP_ZOOM_LEVEL_DE;

    [[nodiscard]] double startupMapLatitude() const { return _startupMapLatitude; }
    void setStartupMapLatitude(double d) { _startupMapLatitude = d; }
    static const QString KEY_STARTUP_MAP_LATITUDE;
    static const double DEFAULT_STARTUP_MAP_LATITUDE_SI;
    static const double DEFAULT_STARTUP_MAP_LATITUDE_DE;

    [[nodiscard]] double startupMapLongitude() const { return _startupMapLongitude; }
    void setStartupMapLongitude(double d) { _startupMapLongitude = d; }
    static const QString KEY_STARTUP_MAP_LONGITUDE;
    static const double DEFAULT_STARTUP_MAP_LONGITUDE_SI;
    static const double DEFAULT_STARTUP_MAP_LONGITUDE_DE;

    // specials
    static const double DEFAULT_MIN_MAP_LATITUDE_SI;
    static const double DEFAULT_MAX_MAP_LATITUDE_SI;
    static const double DEFAULT_MIN_MAP_LONGITUDE_SI;
    static const double DEFAULT_MAX_MAP_LONGITUDE_SI;
    static const double DEFAULT_MIN_MAP_LATITUDE_DE;
    static const double DEFAULT_MAX_MAP_LATITUDE_DE;
    static const double DEFAULT_MIN_MAP_LONGITUDE_DE;
    static const double DEFAULT_MAX_MAP_LONGITUDE_DE;

    void resetStartupMapCoordinates();

    // Locale
    [[nodiscard]] const QString &locale() const { return _locale; }
    void setLocale(const QString &s) { _locale = s; }
    static const QString KEY_LOCALE;
    static const QString DEFAULT_LOCALE;

    // Notifications
    [[nodiscard]] int startupNotificationsSetting() const;

    [[nodiscard]] bool notificationsEnabled() const { return _notificationsEnabled; }
    void setNotificationsEnabled(bool e) { _notificationsEnabled = e; }
    static const QString KEY_NOTIFICATIONS_ENABLED;
    static const bool DEFAULT_NOTIFICATIONS_ENABLED;

    [[nodiscard]] bool notificationsInitialChoice() const { return _notificationsInitialChoice; }
    void setNotificationsInitialChoice(bool e) { _notificationsInitialChoice = e; }
    static const QString KEY_NOTIFICATIONS_INITIAL_CHOICE;
    static const bool DEFAULT_NOTIFICATIONS_INITIAL_CHOICE;

    [[nodiscard]] Weather::AlertSeverity notificationsAlertSeverity() const { return _notificationsAlertSeverity; }
    void setNotificationsAlertSeverity(Weather::AlertSeverity s) { _notificationsAlertSeverity = s; }
    static const QString KEY_NOTIFICATIONS_ALERT_SEVERITY;
    static const Weather::AlertSeverity DEFAULT_NOTIFICATIONS_ALERT_SEVERITY;

    [[nodiscard]] const QStringList &notificationsAlertKeys() const { return _notificationsAlertKeys; }
    void setNotificationsAlertKeys(const QStringList &l) { _notificationsAlertKeys = l; }
    static const QString KEY_NOTIFICATIONS_ALERT_KEYS;
    static const QStringList DEFAULT_NOTIFICATIONS_ALERT_KEYS;

    // GUI
    [[nodiscard]] bool showInTray() const { return _showInTray; }
    void setShowInTray(bool b) { _showInTray = b; }
    static const QString KEY_SHOW_IN_TRAY;
    static const bool DEFAULT_SHOW_IN_TRAY;

#if defined(Q_OS_MACOS)
    [[nodiscard]] bool showInDock() const
    {
        return _showInDock;
    }
    void setShowInDock(bool b) { _showInDock = b; }
    static const QString KEY_SHOW_IN_DOCK;
    static const bool DEFAULT_SHOW_IN_DOCK;
#endif

    // GUI - session
    [[nodiscard]] bool rememberPosition() const { return _rememberPosition; }
    void setRememberPosition(bool b) { _rememberPosition = b; }
    static const QString KEY_REMEMBER_POSITION;
    static const bool DEFAULT_REMEMBER_POSITION;

    [[nodiscard]] bool rememberSize() const { return _rememberSize; }
    void setRememberSize(bool b) { _rememberSize = b; }
    static const QString KEY_REMEMBER_SIZE;
    static const bool DEFAULT_REMEMBER_SIZE;

    [[nodiscard]] int width() const { return _width; }
    void setWidth(int i) { _width = i; }
    static const QString KEY_WIDTH;
    static const int DEFAULT_WIDTH;

    [[nodiscard]] int height() const { return _height; }
    void setHeight(int i) { _height = i; }
    static const QString KEY_HEIGHT;
    static const int DEFAULT_HEIGHT;

    [[nodiscard]] int posX() const { return _posX; }
    void setPosX(int i) { _posX = i; }
    static const QString KEY_POS_X;
    static const int DEFAULT_POS_X;

    [[nodiscard]] int posY() const { return _posY; }
    void setPosY(int i) { _posY = i; }
    static const QString KEY_POS_Y;
    static const int DEFAULT_POS_Y;

    // Special
    [[nodiscard]] const QString &uuid() const { return _uuid; }
    void setUuid(const QString &s) { _uuid = s; }
    static const QString KEY_UUID;
    static const QString DEFAULT_UUID;

signals:
    void settingsReloaded();

private:
    QVariantMap _map;

    // Country selection
    Sources::Country _weatherSource;
    bool _weatherSourceInitialChoice;

    // Location
    Location::Source _locationSource;
    bool _locationInitialChoice;
    QString _locationStation;
    double _locationLatitude;
    double _locationLongitude;

    // Map startup settings
    bool _startupMapEnabled;
    Weather::MapStyle _startupMapStyle;
    Weather::MapType _startupMapType;
    qreal _startupMapZoomLevel;
    double _startupMapLatitude;
    double _startupMapLongitude;

    // Locale
    QString _locale;

    // Notifications
    bool _notificationsEnabled;
    bool _notificationsInitialChoice;
    Weather::AlertSeverity _notificationsAlertSeverity;
    QStringList _notificationsAlertKeys;

    // GUI
    bool _showInTray;
#if defined(Q_OS_MACOS)
    bool _showInDock;
#endif

    // GUI - session
    bool _rememberPosition;
    bool _rememberSize;
    int _width;
    int _height;
    int _posX;
    int _posY;

    // Special
    QString _uuid;
};

} // namespace Vremenar

#endif // VREMENAR_SETTINGS_H_
