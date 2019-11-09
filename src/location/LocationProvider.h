/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_LOCATIONPROVIDER_H_
#define VREMENAR_LOCATIONPROVIDER_H_

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>
#include <QtPositioning/QGeoPositionInfoSource>

namespace Vremenar
{

class LocationProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate initial READ initialPosition CONSTANT)
    Q_PROPERTY(QGeoCoordinate position READ currentPosition NOTIFY positionChanged)
    Q_PROPERTY(QString location READ currentLocation NOTIFY locationChanged)
public:
    explicit LocationProvider(QObject *parent = nullptr);

    [[nodiscard]] QGeoCoordinate initialPosition() const;
    [[nodiscard]] QGeoCoordinate currentPosition() const;
    [[nodiscard]] QString currentLocation() const;

    Q_INVOKABLE void requestPositionUpdate();

Q_SIGNALS:
    void positionChanged();
    void locationChanged();

private Q_SLOTS:
    void positionUpdated(const QGeoPositionInfo &info);
    void positionError(QGeoPositionInfoSource::Error error);
    void positionTimeout();

    void reverseGeocodingFinished(QGeoCodeReply *reply);
    void reverseGeocodingError(QGeoCodeReply *reply,
                               QGeoCodeReply::Error error,
                               const QString &errorString);

private:
    std::unique_ptr<QTimer> _timer{};

    std::unique_ptr<QGeoPositionInfoSource> _position;
    std::unique_ptr<QGeoServiceProvider> _provider;

    QGeoPositionInfo _initialPosition;
    QGeoPositionInfo _currentPosition;
    QGeoLocation _currentLocation;
};

} // namespace Vremenar

#endif // VREMENAR_LOCATIONPROVIDER_H_
