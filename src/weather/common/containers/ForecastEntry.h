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

#ifndef VREMENAR_FORECASTENTRY_H_
#define VREMENAR_FORECASTENTRY_H_

#include <QtPositioning/QGeoCoordinate>

#include "common/ListItem.h"

namespace Vremenar
{

class ForecastEntry : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(qint64 time READ time CONSTANT)
    Q_PROPERTY(QString icon READ icon CONSTANT)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
    Q_PROPERTY(qreal zoomLevel READ zoomLevel CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        TimeRole,
        IconRole,
        CoordinateRole,
        ZoomLevelRole
    };

    explicit ForecastEntry(const QString &id,
                           qint64 time,
                           QString title,
                           QString icon,
                           const QGeoCoordinate &coordinate,
                           qreal zoomLevel,
                           QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] inline qint64 time() const { return _time; }
    [[nodiscard]] inline const QString &icon() const { return _icon; }
    [[nodiscard]] inline const QGeoCoordinate &coordinate() const { return _coordinate; }
    [[nodiscard]] inline qreal zoomLevel() const { return _zoomLevel; }

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {TimeRole, "time"},
            {IconRole, "icon"},
            {CoordinateRole, "coordinate"},
            {ZoomLevelRole, "zoomLevel"}};
    }

private:
    qint64 _time;
    QString _title;
    QString _icon;
    QGeoCoordinate _coordinate;
    qreal _zoomLevel;
};

} // namespace Vremenar

#endif // VREMENAR_FORECASTENTRY_H_