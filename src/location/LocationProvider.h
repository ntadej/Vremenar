/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
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
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoPositionInfoSource>

#include "location/LocationProviderPlatform.h"

namespace Vremenar
{

class StationListModel;

class LocationProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool supported READ supported CONSTANT)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
    Q_PROPERTY(QGeoCoordinate initial READ initialPosition CONSTANT)
    Q_PROPERTY(QGeoCoordinate position READ currentPosition NOTIFY positionChanged)
    Q_PROPERTY(QString location READ currentLocation NOTIFY locationChanged)
public:
    explicit LocationProvider(StationListModel *stations,
                              QObject *parent = nullptr);

    [[nodiscard]] bool supported();
    [[nodiscard]] bool enabled();
    [[nodiscard]] QGeoCoordinate initialPosition() const;
    [[nodiscard]] QGeoCoordinate currentPosition() const;
    [[nodiscard]] QString currentLocation() const;

    Q_INVOKABLE void requestPositionUpdate();
    Q_INVOKABLE [[nodiscard]] bool validate(const QGeoCoordinate &coordinate) const;
    Q_INVOKABLE [[nodiscard]] QGeoCoordinate validateAndCorrect(const QGeoCoordinate &coordinate) const;

signals:
    void enabledChanged(bool);
    void positionChanged(QGeoCoordinate);
    void locationChanged();

public slots:
    void locationSettingsChanged();
    void supportedMethodsChanged();

private slots:
    void positionUpdated(const QGeoPositionInfo &info);
    void positionError(QGeoPositionInfoSource::Error error);
    void positionTimeout();

    void reverseGeocodingFinished(QGeoCodeReply *reply);
    void reverseGeocodingError(QGeoCodeReply *reply,
                               QGeoCodeReply::Error error,
                               const QString &errorString);

private:
    void initPosition();
#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    void initMacOSiOS();
#elif defined(Q_OS_ANDROID)
    bool initAndroid();
#endif

    std::unique_ptr<LocationProviderPlatform> _platform{};

    std::unique_ptr<QTimer> _timer{};

    std::unique_ptr<QGeoPositionInfoSource> _position{};
    std::unique_ptr<QGeoServiceProvider> _provider{};

    StationListModel *_stations{}; // not owned here

    QGeoPositionInfo _initialPosition;
    QGeoPositionInfo _currentPosition;
    QGeoLocation _currentLocation;

    QGeoPositionInfoSource::PositioningMethods _currentSupportedMethods;
    bool _hasFatalError{};
};

} // namespace Vremenar

#endif // VREMENAR_LOCATIONPROVIDER_H_
