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

#ifndef VREMENAR_WEATHERINFO_H_
#define VREMENAR_WEATHERINFO_H_

#include <QtPositioning/QGeoCoordinate>

#include "common/ListItem.h"
#include "weather/common/Weather.h"

namespace Vremenar
{

class WeatherInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display NOTIFY updated)
    Q_PROPERTY(Weather::ObservationType observation READ observation NOTIFY updated)
    Q_PROPERTY(qint64 time READ time NOTIFY updated)
    Q_PROPERTY(QString icon READ icon NOTIFY updated)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
    Q_PROPERTY(qreal zoomLevel READ zoomLevel CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        ObservationRole,
        TimeRole,
        IconRole,
        TemperatureRole,
        TemperatureLowRole,
        CoordinateRole,
        ZoomLevelRole
    };

    explicit WeatherInfo(const QString &id,
                         Weather::ObservationType observation,
                         qint64 time,
                         QString title,
                         QString icon,
                         qreal temperature,
                         qreal temperatureLow,
                         const QGeoCoordinate &coordinate,
                         qreal zoomLevel,
                         QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] inline Weather::ObservationType observation() const { return _observation; }
    [[nodiscard]] inline qint64 time() const { return _time; }
    [[nodiscard]] inline const QString &icon() const { return _icon; }
    [[nodiscard]] inline qreal temperature() const { return _temperature; }
    [[nodiscard]] inline qreal temperatureLow() const { return _temperatureLow; }
    [[nodiscard]] inline const QGeoCoordinate &coordinate() const { return _coordinate; }
    [[nodiscard]] inline qreal zoomLevel() const { return _zoomLevel; }

    void update(const WeatherInfo *source);

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {ObservationRole, "observation"},
            {TimeRole, "time"},
            {IconRole, "icon"},
            {TemperatureRole, "temperature"},
            {TemperatureLowRole, "temperatureLow"},
            {CoordinateRole, "coordinate"},
            {ZoomLevelRole, "zoomLevel"}};
    }

Q_SIGNALS:
    void updated();

private:
    Weather::ObservationType _observation;
    qint64 _time;
    QString _title;
    QString _icon;
    qreal _temperature;
    qreal _temperatureLow;
    QGeoCoordinate _coordinate;
    qreal _zoomLevel;
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERINFO_H_
