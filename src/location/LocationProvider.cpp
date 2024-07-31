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

#include "location/LocationProvider.h"

#include "location/Location.h"
#include "settings/Settings.h"
#include "weather/Sources.h"
#include "weather/containers/StationInfo.h"
#include "weather/models/StationListModel.h"

#include "Config.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QLocationPermission>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoServiceProvider>
#include <QtPositioning/QGeoAddress>
#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoPositionInfo>
#include <QtPositioning/QGeoPositionInfoSource>

#include <memory>

using Qt::Literals::StringLiterals::operator""_s;

#ifdef VREMENAR_POSITIONING
namespace
{
constexpr int updateInterval{60000000};
#ifdef Q_OS_ANDROID
constexpr int androidQuickUpdate{3000};
#endif
} // namespace
#endif

namespace Vremenar
{

LocationProvider::LocationProvider(StationListModel *stations, QObject *parent)
    : QObject(parent),
#ifdef VREMENAR_POSITIONING
      _timer(std::make_unique<QTimer>(this)),
#endif
      _stations(stations)
{
    const Settings settings(this);
    _initialPosition = QGeoPositionInfo(QGeoCoordinate(settings.startupMapLatitude(), settings.startupMapLongitude()), QDateTime::currentDateTime());

#ifdef VREMENAR_POSITIONING
    _timer->setInterval(updateInterval);
    _timer->setSingleShot(true);
#endif

    QMap<QString, QVariant> params;
    params.insert(u"osm.useragent"_s, QString(Vremenar::name) + " " + Vremenar::version);

    _provider = std::make_unique<QGeoServiceProvider>("osm", params);
    if (_provider->geocodingManager() != nullptr) {
        connect(_provider->geocodingManager(), &QGeoCodingManager::finished, this, &LocationProvider::reverseGeocodingFinished);
        connect(_provider->geocodingManager(), &QGeoCodingManager::errorOccurred, this, &LocationProvider::reverseGeocodingError);
    }
}

void LocationProvider::initPosition()
{
#ifdef VREMENAR_POSITIONING
    if (_position != nullptr) {
        requestPositionUpdate();
        return;
    }

    QLocationPermission locationPermission;
    locationPermission.setAccuracy(QLocationPermission::Approximate);
    locationPermission.setAvailability(QLocationPermission::WhenInUse);
    switch (qApp->checkPermission(locationPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qDebug() << "Requesting positioning";
        qApp->requestPermission(locationPermission, this, &LocationProvider::initPosition);
        return;
    case Qt::PermissionStatus::Denied:
        qDebug() << "Positioning not allowed";
        return;
    case Qt::PermissionStatus::Granted:
        qDebug() << "Positioning allowed";
    }

    _position.reset(QGeoPositionInfoSource::createDefaultSource(this));
    if (_position != nullptr) {
        connect(_timer.get(), &QTimer::timeout, this, &LocationProvider::requestPositionUpdate);

        connect(_position.get(), &QGeoPositionInfoSource::supportedPositioningMethodsChanged, this, &LocationProvider::supportedMethodsChanged);
        connect(_position.get(), &QGeoPositionInfoSource::positionUpdated, this, &LocationProvider::positionUpdated);
        connect(_position.get(), &QGeoPositionInfoSource::errorOccurred, this, &LocationProvider::positionError);

        positionUpdated(_position->lastKnownPosition());
        requestPositionUpdate();
        qDebug() << "Positioning initialised";
    } else {
        qWarning() << "Positioning source could not be initialised.";
    }
#endif
}

bool LocationProvider::supported()
{
#ifndef VREMENAR_POSITIONING
    return false;
#else
    return true;
#endif
}

bool LocationProvider::enabled()
{
    const Settings settings(this);
    if (!settings.locationInitialChoice() || settings.locationSource() == Location::Disabled) {
        return false;
    }

    if (settings.locationSource() == Location::Automatic) {
#ifndef VREMENAR_POSITIONING
        return false;
#else
        QLocationPermission locationPermission;
        locationPermission.setAccuracy(QLocationPermission::Approximate);
        locationPermission.setAvailability(QLocationPermission::WhenInUse);
        switch (qApp->checkPermission(locationPermission)) {
        case Qt::PermissionStatus::Undetermined:
        case Qt::PermissionStatus::Denied:
            return false;
        case Qt::PermissionStatus::Granted:
            break;
        }

        if (!_hasFatalError && _position != nullptr) {
            const QGeoPositionInfoSource::PositioningMethods methods = _position->supportedPositioningMethods();
            const bool status = methods != 0 && !methods.testFlag(QGeoPositionInfoSource::NoPositioningMethods);
            if (_currentSupportedMethods != methods) {
                qDebug() << "Supported positioning methods:" << methods;
                emit enabledChanged(status);
                _currentSupportedMethods = methods;
            }
            return status;
        }

        return false;
#endif
    }

    return (settings.locationSource() == Location::Coordinate && (settings.locationLatitude() != 0 || settings.locationLongitude() != 0))
           || (settings.locationSource() == Location::Station && !settings.locationStation().isEmpty());
}

void LocationProvider::resetPosition()
{
    const Settings settings(this);
    _initialPosition = QGeoPositionInfo(QGeoCoordinate(settings.startupMapLatitude(), settings.startupMapLongitude()), QDateTime::currentDateTime());

    emit initialPositionChanged(_initialPosition.coordinate());
}

void LocationProvider::requestPositionUpdate()
{
#ifdef VREMENAR_POSITIONING
    const Settings settings(this);
    if (settings.locationSource() != Location::Automatic) {
        emit positionChanged(_currentPosition.coordinate());
        return;
    }

    _timer->stop();
    if (_position != nullptr && enabled()) {
        qDebug() << "Request position update.";
#ifdef Q_OS_ANDROID
        _position->requestUpdate(androidQuickUpdate);
#else
        _position->requestUpdate();
#endif
    }
#endif
}

bool LocationProvider::validate(const QGeoCoordinate &coordinate) const
{
    const Settings settings;
    const Sources::Country country = settings.weatherSource();
    if (country == Sources::Slovenia) {
        if (Settings::DEFAULT_MIN_MAP_LATITUDE_SI > coordinate.latitude()
            || Settings::DEFAULT_MAX_MAP_LATITUDE_SI < coordinate.latitude()
            || Settings::DEFAULT_MIN_MAP_LONGITUDE_SI > coordinate.longitude()
            || Settings::DEFAULT_MAX_MAP_LONGITUDE_SI < coordinate.longitude()) {
            return false;
        }
    } else if (country == Sources::Germany) {
        if (Settings::DEFAULT_MIN_MAP_LATITUDE_DE > coordinate.latitude()
            || Settings::DEFAULT_MAX_MAP_LATITUDE_DE < coordinate.latitude()
            || Settings::DEFAULT_MIN_MAP_LONGITUDE_DE > coordinate.longitude()
            || Settings::DEFAULT_MAX_MAP_LONGITUDE_DE < coordinate.longitude()) {
            return false;
        }
    }

    return true;
}

QGeoCoordinate LocationProvider::validateAndCorrect(const QGeoCoordinate &coordinate) const
{
    const bool valid = validate(coordinate);
    if (valid) {
        return coordinate;
    }

    QGeoCoordinate newCoordinate = coordinate;
    const Settings settings;
    const Sources::Country country = settings.weatherSource();
    if (country == Sources::Slovenia) {
        if (Settings::DEFAULT_MIN_MAP_LATITUDE_SI > coordinate.latitude()) {
            newCoordinate.setLatitude(Settings::DEFAULT_MIN_MAP_LATITUDE_SI);
        }
        if (Settings::DEFAULT_MAX_MAP_LATITUDE_SI < coordinate.latitude()) {
            newCoordinate.setLatitude(Settings::DEFAULT_MAX_MAP_LATITUDE_SI);
        }
        if (Settings::DEFAULT_MIN_MAP_LONGITUDE_SI > coordinate.longitude()) {
            newCoordinate.setLongitude(Settings::DEFAULT_MIN_MAP_LONGITUDE_SI);
        }
        if (Settings::DEFAULT_MAX_MAP_LONGITUDE_SI < coordinate.longitude()) {
            newCoordinate.setLongitude(Settings::DEFAULT_MAX_MAP_LONGITUDE_SI);
        }
    } else if (country == Sources::Germany) {
        if (Settings::DEFAULT_MIN_MAP_LATITUDE_DE > coordinate.latitude()) {
            newCoordinate.setLatitude(Settings::DEFAULT_MIN_MAP_LATITUDE_DE);
        }
        if (Settings::DEFAULT_MAX_MAP_LATITUDE_DE < coordinate.latitude()) {
            newCoordinate.setLatitude(Settings::DEFAULT_MAX_MAP_LATITUDE_DE);
        }
        if (Settings::DEFAULT_MIN_MAP_LONGITUDE_DE > coordinate.longitude()) {
            newCoordinate.setLongitude(Settings::DEFAULT_MIN_MAP_LONGITUDE_DE);
        }
        if (Settings::DEFAULT_MAX_MAP_LONGITUDE_DE < coordinate.longitude()) {
            newCoordinate.setLongitude(Settings::DEFAULT_MAX_MAP_LONGITUDE_DE);
        }
    }

    return newCoordinate;
}

QGeoCoordinate LocationProvider::initialPosition() const
{
    return _initialPosition.coordinate();
}

QGeoCoordinate LocationProvider::currentPosition() const
{
    return _currentPosition.coordinate();
}

QString LocationProvider::currentLocation() const
{
    return _currentLocation.address().street();
}

void LocationProvider::positionUpdated(const QGeoPositionInfo &info)
{
    if (!info.isValid()) {
        return;
    }

    qDebug() << "Position updated:" << info;

    _currentPosition = info;

    // validate
    if (!validate(_currentPosition.coordinate())) {
        _currentPosition.setCoordinate(QGeoCoordinate());
    }

    // Request location info about position
    if (_provider->geocodingManager() != nullptr) {
        if (_currentPosition.isValid()) {
            _provider->geocodingManager()->reverseGeocode(info.coordinate());
        }
    } else {
        qWarning() << "No geocoding provider available.";
    }

#ifdef VREMENAR_POSITIONING
    _timer->start();
#endif

    emit positionChanged(_currentPosition.coordinate());
}

void LocationProvider::positionError(QGeoPositionInfoSource::Error error)
{
    // TODO(#1): pass errors to UI
    switch (error) {
    case QGeoPositionInfoSource::AccessError:
        qWarning() << "This application is not allowed to do positioning.";
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
#ifdef VREMENAR_POSITIONING
        _hasFatalError = true;
#endif
        emit enabledChanged(false);
#endif
        break;
    case QGeoPositionInfoSource::ClosedError:
        qWarning() << "The connection was closed before the position could be obtained.";
        break;
    default:
        break;
    }
}

void LocationProvider::positionTimeout()
{
    qWarning() << "Positioning has timed-out.";
}

void LocationProvider::locationSettingsChanged()
{
    const Settings settings(this);
    if (settings.locationSource() == Location::Automatic) {
        initPosition();
    } else if (settings.locationSource() == Location::Station) {
        auto *station = _stations->find<StationInfo>(settings.locationStation());
        if (station == nullptr || station->id().isEmpty()) {
            emit enabledChanged(enabled());
            return;
        }
        const QGeoPositionInfo info(station->coordinate(), QDateTime::currentDateTime());
        positionUpdated(info);
    } else if (settings.locationSource() == Location::Coordinate) {
        if (settings.locationLatitude() == 0 && settings.locationLongitude() == 0) {
            emit enabledChanged(enabled());
            return;
        }
        const QGeoPositionInfo info(QGeoCoordinate(settings.locationLatitude(), settings.locationLongitude()), QDateTime::currentDateTime());
        positionUpdated(info);
    }

    emit enabledChanged(enabled());
}

void LocationProvider::supportedMethodsChanged()
{
    if (_position == nullptr) {
        return;
    }

    _currentSupportedMethods = _position->supportedPositioningMethods();

    qDebug() << "Supported positioning methods changed to:" << _currentSupportedMethods;

    emit enabledChanged(enabled());

    requestPositionUpdate();
}

void LocationProvider::reverseGeocodingFinished(QGeoCodeReply *reply)
{
    if (!reply->isFinished() || reply->error() != QGeoCodeReply::NoError) {
        return;
    }

    if (reply->locations().isEmpty()) {
        _currentLocation = QGeoLocation();
        return;
    }

    _currentLocation = reply->locations().constFirst();
    qDebug() << "Location updated:"
             << _currentLocation.address().street()
             << _currentLocation.address().city();

    emit locationChanged();
}

void LocationProvider::reverseGeocodingError(QGeoCodeReply *reply,
                                             QGeoCodeReply::Error error,
                                             const QString &errorString)
{
    Q_UNUSED(reply)

    qWarning() << "Reverse Geocoding Error:" << error << errorString;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_LocationProvider.cpp"
// NOLINTEND
