/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
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

namespace Vremenar
{

class MapLayer : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(Weather::MapType type READ type CONSTANT)
    Q_PROPERTY(QDateTime time READ time CONSTANT)
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QGeoRectangle range READ range CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        TypeRole,
        TimeRole,
        TimestampRole,
        UrlRole,
        MinLatitudeRole,
        MinLongitudeRole,
        MaxLatitudeRole,
        MaxLongitudeRole,
        CoordinatesRole
    };

    explicit MapLayer(Weather::MapType type,
                      const QDateTime &time,
                      const QUrl &url,
                      const QGeoRectangle &range,
                      QObject *parent = nullptr);

    // Implemented virtual functions
    virtual QVariant data(int role) const final;
    virtual QString display() const final;

    inline Weather::MapType type() const { return _type; }
    inline const QDateTime &time() const { return _time; }
    inline const QUrl &url() const { return _url; }
    inline const QGeoRectangle &range() const { return _range; }
    inline const QVariant &coordinates() const { return _coordinates; }

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {TypeRole, "type"},
            {TimeRole, "time"},
            {TimestampRole, "timestamp"},
            {UrlRole, "url"},
            {MinLatitudeRole, "minLatitude"},
            {MinLongitudeRole, "minLongitude"},
            {MaxLatitudeRole, "maxLatitude"},
            {MaxLongitudeRole, "maxLongitude"},
            {CoordinatesRole, "coordinates"}};
    }

private:
    Weather::MapType _type;
    QDateTime _time;
    QUrl _url;
    QGeoRectangle _range;
    QVariant _coordinates;
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYER_H_
