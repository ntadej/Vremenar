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

#ifndef VREMENAR_WEATHERCONDITION_H_
#define VREMENAR_WEATHERCONDITION_H_

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QHash>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <cstdint>
#include <memory>

namespace Vremenar
{

class WeatherCondition : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display NOTIFY updated)
    Q_PROPERTY(QString displayTemperature READ displayTemperature NOTIFY updated)
    Q_PROPERTY(QString displayTemperatureShort READ displayTemperatureShort NOTIFY updated)
    Q_PROPERTY(Weather::ObservationType observation READ observation NOTIFY updated)
    Q_PROPERTY(qint64 time READ time NOTIFY updated)
    Q_PROPERTY(QString icon READ icon NOTIFY updated)
    Q_PROPERTY(qreal temperature READ temperature NOTIFY updated)
    Q_PROPERTY(qreal temperatureLow READ temperatureLow NOTIFY updated)
public:
    enum Roles : std::uint16_t {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        ObservationRole,
        TimeRole,
        IconRole,
        TemperatureRole,
        TemperatureLowRole,
        DisplayTemperatureRole,
        DisplayTemperatureShortRole
    };

    explicit WeatherCondition(Weather::ObservationType observation,
                              qint64 time,
                              QString icon,
                              qreal temperature,
                              qreal temperatureLow,
                              QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] static std::unique_ptr<WeatherCondition> fromJson(const QJsonObject &json);

    [[nodiscard]] QString displayTemperature() const;
    [[nodiscard]] QString displayTemperatureShort() const;

    [[nodiscard]] Weather::ObservationType observation() const { return _observation; }
    [[nodiscard]] qint64 time() const { return _time; }
    [[nodiscard]] const QString &icon() const { return _icon; }
    [[nodiscard]] qreal temperature() const { return _temperature; }
    [[nodiscard]] qreal temperatureLow() const { return _temperatureLow; }

    void update(const WeatherCondition *source);

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {ObservationRole, "observation"},
            {TimeRole, "time"},
            {IconRole, "icon"},
            {TemperatureRole, "temperature"},
            {TemperatureLowRole, "temperatureLow"},
            {DisplayTemperatureRole, "displayTemperature"},
            {DisplayTemperatureShortRole, "displayTemperatureShort"}};
    }

signals:
    void updated();

private:
    Weather::ObservationType _observation;
    qint64 _time;
    QString _icon;
    qreal _temperature;
    qreal _temperatureLow;
};

} // namespace Vremenar

// NOLINTNEXTLINE
Q_DECLARE_METATYPE(Vremenar::WeatherCondition *)

#endif // VREMENAR_WEATHERCONDITION_H_
