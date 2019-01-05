/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LOCATIONPROVIDER_H_
#define VREMENAR_LOCATIONPROVIDER_H_

#include <QtCore/QObject>
#include <QtLocation/QGeoCodeReply>
#include <QtLocation/QGeoServiceProvider>
#include <QtPositioning/QGeoPositionInfoSource>

namespace Vremenar
{

class LocationProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate position READ currentPosition NOTIFY positionChanged)
    Q_PROPERTY(QString location READ currentLocation NOTIFY locationChanged)
public:
    explicit LocationProvider(QObject *parent = nullptr);
    ~LocationProvider() = default;

    static QString mapboxAPIToken();

    QGeoCoordinate currentPosition() const;
    QString currentLocation() const;

signals:
    void positionChanged();
    void locationChanged();

private slots:
    void positionUpdated(const QGeoPositionInfo &info);
    void positionError(QGeoPositionInfoSource::Error error);
    void positionTimeout();

    void reverseGeocodingFinished(QGeoCodeReply *reply);
    void reverseGeocodingError(QGeoCodeReply *reply,
                               QGeoCodeReply::Error error,
                               const QString &errorString);

private:
    std::unique_ptr<QGeoPositionInfoSource> _position;
    std::unique_ptr<QGeoServiceProvider> _provider;

    QGeoPositionInfo _currentPosition;
    QGeoLocation _currentLocation;
};

} // namespace Vremenar

#endif // VREMENAR_LOCATIONPROVIDER_H_
