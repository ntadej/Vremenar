/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtLocation/QGeoCodingManager>
#include <QtPositioning/QGeoAddress>

#include "common/Common.h"
#include "location/LocationProvider.h"

LocationProvider::LocationProvider(QObject *parent)
    : QObject(parent)
{
    QMap<QString, QVariant> params;
    params["osm.useragent"] = Vremenar::name() + " " + Vremenar::version();

    _provider = new QGeoServiceProvider("osm", params);
    if (_provider->geocodingManager()) {
        connect(_provider->geocodingManager(), SIGNAL(finished(QGeoCodeReply *)),
                this, SLOT(reverseGeocodingFinished(QGeoCodeReply *)));
        connect(_provider->geocodingManager(), SIGNAL(error(QGeoCodeReply *, QGeoCodeReply::Error, QString)),
                this, SLOT(reverseGeocodingError(QGeoCodeReply *, QGeoCodeReply::Error, QString)));
    }

    _position = QGeoPositionInfoSource::createDefaultSource(this);
    if (_position) {
        connect(_position, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        connect(_position, SIGNAL(error(QGeoPositionInfoSource::Error)),
                this, SLOT(positionError(QGeoPositionInfoSource::Error)));
        connect(_position, SIGNAL(updateTimeout()), this, SLOT(positionTimeout()));
        _position->requestUpdate(15000);
    } else {
        qWarning() << "Positioning source could not be initialised.";
    }
}

LocationProvider::~LocationProvider() {}

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
    qDebug() << "Position updated:" << info;

    _currentPosition = info;

    // Request location info about position
    if (_provider->geocodingManager()) {
        _provider->geocodingManager()->reverseGeocode(info.coordinate());
    } else {
        qWarning() << "No geocoding provider available.";
    }

    emit positionChanged();
}

void LocationProvider::positionError(QGeoPositionInfoSource::Error error)
{
    // TODO: pass errors to UI
    switch (error) {
    case QGeoPositionInfoSource::AccessError:
        qWarning() << "This application is not allowed to do positioning.";
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

void LocationProvider::reverseGeocodingFinished(QGeoCodeReply *reply)
{
    if (!reply->isFinished() || reply->error() != QGeoCodeReply::NoError)
        return;

    if (reply->locations().isEmpty()) {
        _currentLocation = QGeoLocation();
        return;
    }

    _currentLocation = reply->locations().first();
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

QString LocationProvider::mapboxAPIToken()
{
#ifdef MAPBOX_API_TOKEN
    return QString(MAPBOX_API_TOKEN);
#else
    return QString();
#endif
}