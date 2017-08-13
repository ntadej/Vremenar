/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>

#include "location/LocationProvider.h"

LocationProvider::LocationProvider(QObject *parent)
    : QObject(parent)
{
    QMap<QString, QVariant> params;
    params["here.app_id"] = providerAppId();
    params["here.token"] = providerAppToken();

    _provider = new QGeoServiceProvider("here", params);
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

void LocationProvider::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Position updated:" << info;
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

QString LocationProvider::providerAppId()
{
#ifdef HERE_APP_ID
    return QString(HERE_APP_ID);
#else
    return QString();
#endif
}

QString LocationProvider::providerAppToken()
{
#ifdef HERE_APP_TOKEN
    return QString(HERE_APP_TOKEN);
#else
    return QString();
#endif
}
