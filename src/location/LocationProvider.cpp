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

#include <QtCore/QDebug>
#include <QtLocation/QGeoCodingManager>
#include <QtPositioning/QGeoAddress>

#include "location/LocationProvider.h"
#include "settings/Settings.h"

#include "Config.h"

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

LocationProvider::LocationProvider(QObject *parent)
    : QObject(parent),
      _timer(std::make_unique<QTimer>(this))
{
#if defined(VREMENAR_POSITIONING) && (defined(Q_OS_MACOS) || defined(Q_OS_IOS))
    initMacOSiOS();
#endif

    Settings settings(this);
    _initialPosition = QGeoPositionInfo(QGeoCoordinate(settings.startupMapLatitude(), settings.startupMapLongitude()), QDateTime::currentDateTime());

#ifdef VREMENAR_POSITIONING
#if defined(Q_OS_ANDROID)
    if (!initAndroid()) {
        return;
    }
#endif

    _timer->setInterval(updateInterval);
    _timer->setSingleShot(true);

    QMap<QString, QVariant> params;
    params.insert(QStringLiteral("osm.useragent"), QString(Vremenar::name) + " " + Vremenar::version);

    _provider = std::make_unique<QGeoServiceProvider>("osm", params);
    if (_provider->geocodingManager() != nullptr) {
        connect(_provider->geocodingManager(), &QGeoCodingManager::finished,
                this, &LocationProvider::reverseGeocodingFinished);
        connect(_provider->geocodingManager(), &QGeoCodingManager::error,
                this, &LocationProvider::reverseGeocodingError);
    }

    _position.reset(QGeoPositionInfoSource::createDefaultSource(this));
    if (_position) {
        connect(_timer.get(), &QTimer::timeout, this, &LocationProvider::requestPositionUpdate);

        connect(_position.get(), &QGeoPositionInfoSource::supportedPositioningMethodsChanged,
                this, &LocationProvider::supportedMethodsChanged);
        connect(_position.get(), &QGeoPositionInfoSource::positionUpdated,
                this, &LocationProvider::positionUpdated);
        connect(_position.get(), QOverload<QGeoPositionInfoSource::Error>::of(&QGeoPositionInfoSource::error),
                this, &LocationProvider::positionError);
        connect(_position.get(), &QGeoPositionInfoSource::updateTimeout,
                this, &LocationProvider::positionTimeout);

        positionUpdated(_position->lastKnownPosition());
        requestPositionUpdate();
    } else {
        qWarning() << "Positioning source could not be initialised.";
    }
#endif
}

bool LocationProvider::enabled()
{
#ifndef VREMENAR_POSITIONING
    return false;
#elif defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    return _platform->servicesEnabled() && _platform->servicesAllowed();
#else
    if (_position != nullptr) {
        QGeoPositionInfoSource::PositioningMethods methods = _position->supportedPositioningMethods();
        if (_currentSupportedMethods != methods) {
            qDebug() << "Supported positioning methods:" << methods;
            Q_EMIT enabledChanged();
            _currentSupportedMethods = methods;
        }
        return !(methods == 0 || methods.testFlag(QGeoPositionInfoSource::NoPositioningMethods));
    }

    return false;
#endif
}

void LocationProvider::requestPositionUpdate()
{
#ifdef VREMENAR_POSITIONING
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

    // Request location info about position
    if (_provider->geocodingManager() != nullptr) {
        _provider->geocodingManager()->reverseGeocode(info.coordinate());
    } else {
        qWarning() << "No geocoding provider available.";
    }

    _timer->start();

    Q_EMIT positionChanged(_currentPosition.coordinate());
}

void LocationProvider::positionError(QGeoPositionInfoSource::Error error)
{
    // TODO(#1): pass errors to UI
    switch (error) {
    case QGeoPositionInfoSource::AccessError:
        qWarning() << "This application is not allowed to do positioning.";
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
        if (_position != nullptr) {
            // this leaks a bit but the application crashes otherwise
            _position.release();
            Q_EMIT enabledChanged();
        }
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

void LocationProvider::supportedMethodsChanged()
{
    if (_position == nullptr) {
        return;
    }

    _currentSupportedMethods = _position->supportedPositioningMethods();

    qDebug() << "Supported positioning methods changed to:" << _currentSupportedMethods;

    Q_EMIT enabledChanged();

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

    Q_EMIT locationChanged();
}

void LocationProvider::reverseGeocodingError(QGeoCodeReply *reply,
                                             QGeoCodeReply::Error error,
                                             const QString &errorString)
{
    Q_UNUSED(reply)

    qWarning() << "Reverse Geocoding Error:" << error << errorString;
}

} // namespace Vremenar
