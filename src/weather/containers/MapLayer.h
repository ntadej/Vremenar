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

#ifndef VREMENAR_MAPLAYER_H_
#define VREMENAR_MAPLAYER_H_

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QDateTime>
#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QVariant>
#include <QtPositioning/QGeoRectangle>

#include <cstdint>

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
    Q_PROPERTY(QString url READ url CONSTANT)
    Q_PROPERTY(QGeoRectangle bbox READ bbox NOTIFY bboxChanged)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged)

public:
    enum Roles : std::uint16_t {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        ObservationRole,
        SourceRole,
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

    explicit MapLayer(Weather::Source source,
                      Weather::MapType type,
                      Weather::MapRenderingType rendering,
                      Weather::ObservationType observation,
                      const QDateTime &time,
                      QString url,
                      const QGeoRectangle &bbox = QGeoRectangle(),
                      QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] Weather::Source source() const { return _source; }
    [[nodiscard]] Weather::ObservationType observation() const { return _observation; }
    [[nodiscard]] Weather::MapType type() const { return _type; }
    [[nodiscard]] Weather::MapRenderingType rendering() const { return _rendering; }
    [[nodiscard]] const QDateTime &time() const { return _time; }
    [[nodiscard]] const QString &url() const { return _url; }
    [[nodiscard]] const QGeoRectangle &bbox() const { return _bbox; }
    void setBbox(const QGeoRectangle &bbox);
    [[nodiscard]] const QVariant &coordinates() const { return _coordinates; }
    [[nodiscard]] bool loaded() const { return _loaded; }
    void setLoaded();

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {ObservationRole, "observation"},
            {SourceRole, "source"},
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

signals:
    void loadedChanged();
    void bboxChanged();

private:
    Weather::Source _source{Weather::Global};
    Weather::ObservationType _observation{Weather::Recent};
    Weather::MapType _type{Weather::UnknownMapType};
    Weather::MapRenderingType _rendering{Weather::ImageRendering};
    QDateTime _time;
    QString _url;
    QGeoRectangle _bbox;
    QVariant _coordinates;
    bool _loaded{false};
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYER_H_
