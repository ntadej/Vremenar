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

#ifndef VREMENAR_WEATHERINFO_H_
#define VREMENAR_WEATHERINFO_H_

#include "common/ListItem.h"
#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtPositioning/QGeoCoordinate>

#include <cstdint>
#include <memory>

namespace Vremenar
{

class WeatherInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display NOTIFY updated)
    Q_PROPERTY(StationInfo *station READ station CONSTANT)
    Q_PROPERTY(WeatherCondition *condition READ condition NOTIFY updated)
public:
    enum Roles : std::uint16_t {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        StationRole,
        ConditionRole
    };

    explicit WeatherInfo(std::unique_ptr<StationInfo> station,
                         std::unique_ptr<WeatherCondition> condition,
                         QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] StationInfo *station() const { return _station.get(); }
    [[nodiscard]] WeatherCondition *condition() const { return _condition.get(); }

    void update(const WeatherInfo *source);

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {StationRole, "station"},
            {ConditionRole, "condition"}};
    }

signals:
    void updated();

private:
    std::unique_ptr<StationInfo> _station;
    std::unique_ptr<WeatherCondition> _condition;
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERINFO_H_
