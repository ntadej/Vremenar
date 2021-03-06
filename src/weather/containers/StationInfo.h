/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_STATIONINFO_H_
#define VREMENAR_STATIONINFO_H_

#include <memory>

#include <QtCore/QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "common/ListItem.h"

namespace Vremenar
{

class StationInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
    Q_PROPERTY(qreal zoomLevel READ zoomLevel CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        CoordinateRole,
        ZoomLevelRole
    };

    explicit StationInfo(const QString &id,
                         QString name,
                         const QGeoCoordinate &coordinate,
                         qreal zoomLevel,
                         QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] static std::unique_ptr<StationInfo> fromJson(const QJsonObject &json);

    [[nodiscard]] inline const QGeoCoordinate &coordinate() const { return _coordinate; }
    [[nodiscard]] inline qreal zoomLevel() const { return _zoomLevel; }

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {CoordinateRole, "coordinate"},
            {ZoomLevelRole, "zoomLevel"}};
    }

private:
    QString _name;
    QGeoCoordinate _coordinate;
    qreal _zoomLevel;
};

} // namespace Vremenar

Q_DECLARE_METATYPE(Vremenar::StationInfo *)

#endif // VREMENAR_STATIONINFO_H_
