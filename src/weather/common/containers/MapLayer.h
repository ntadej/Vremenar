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
    Q_PROPERTY(Weather::ObservationType observation READ observation CONSTANT)
    Q_PROPERTY(Weather::MapType type READ type CONSTANT)
    Q_PROPERTY(Weather::MapRenderingType rendering READ rendering CONSTANT)
    Q_PROPERTY(QDateTime time READ time CONSTANT)
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QGeoRectangle bbox READ bbox CONSTANT)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        ObservationRole,
        TypeRole,
        RenderingRole,
        TimeRole,
        TimestampRole,
        UrlRole,
        MinLatitudeRole,
        MinLongitudeRole,
        MaxLatitudeRole,
        MaxLongitudeRole,
        CoordinatesRole,
        LoadedRole
    };

    explicit MapLayer(Weather::MapType type,
                      Weather::MapRenderingType rendering,
                      Weather::ObservationType observation,
                      const QDateTime &time,
                      const QUrl &url,
                      const QGeoRectangle &bbox = QGeoRectangle(),
                      QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] inline Weather::ObservationType observation() const { return _observation; }
    [[nodiscard]] inline Weather::MapType type() const { return _type; }
    [[nodiscard]] inline Weather::MapRenderingType rendering() const { return _rendering; }
    [[nodiscard]] inline const QDateTime &time() const { return _time; }
    [[nodiscard]] inline const QUrl &url() const { return _url; }
    [[nodiscard]] inline const QGeoRectangle &bbox() const { return _bbox; }
    void setBbox(const QGeoRectangle &bbox);
    [[nodiscard]] inline const QVariant &coordinates() const { return _coordinates; }
    [[nodiscard]] inline bool loaded() const { return _loaded; }
    void setLoaded();

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {ObservationRole, "observation"},
            {TypeRole, "type"},
            {RenderingRole, "rendering"},
            {TimeRole, "time"},
            {TimestampRole, "timestamp"},
            {UrlRole, "url"},
            {MinLatitudeRole, "minLatitude"},
            {MinLongitudeRole, "minLongitude"},
            {MaxLatitudeRole, "maxLatitude"},
            {MaxLongitudeRole, "maxLongitude"},
            {CoordinatesRole, "coordinates"},
            {LoadedRole, "loaded"}};
    }

    static QVariant geoRectangleToList(const QGeoRectangle &rect);

Q_SIGNALS:
    void loadedChanged();

private:
    Weather::ObservationType _observation{Weather::Recent};
    Weather::MapType _type{Weather::UnknownMap};
    Weather::MapRenderingType _rendering{Weather::ImageRendering};
    QDateTime _time;
    QUrl _url;
    QGeoRectangle _bbox;
    QVariant _coordinates;
    bool _loaded{false};
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYER_H_
