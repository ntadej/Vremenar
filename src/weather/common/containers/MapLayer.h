/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MAPLAYER_H_
#define VREMENAR_MAPLAYER_H_

#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include <QtPositioning/QGeoRectangle>

#include "common/ListItem.h"
#include "weather/common/Weather.h"

class MapLayer : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(Vremenar::Weather::MapType type READ type CONSTANT)
    Q_PROPERTY(QDateTime time READ time CONSTANT)
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QGeoRectangle range READ range CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        TypeRole,
        TimeRole,
        UrlRole,
        MinLatitude,
        MinLongitude,
        MaxLatitude,
        MaxLongitude
    };

    explicit MapLayer(QObject *parent = nullptr);
    explicit MapLayer(Vremenar::Weather::MapType type,
                      const QDateTime &time,
                      const QUrl &url,
                      const QGeoRectangle &range,
                      QObject *parent = nullptr);
    ~MapLayer();

    // Implemented virtual functions
    QString id() const override;
    QVariant data(int role) const override;
    QString display() const override;
    QHash<int, QByteArray> roleNames() const override;

    inline Vremenar::Weather::MapType type() const { return _type; }
    inline QDateTime time() const { return _time; }
    inline QUrl url() const { return _url; }
    inline QGeoRectangle range() const { return _range; }

private:
    Vremenar::Weather::MapType _type;
    QDateTime _time;
    QUrl _url;
    QGeoRectangle _range;
};

#endif // VREMENAR_MAPLAYER_H_
