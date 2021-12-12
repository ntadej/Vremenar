/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_WEATHERINFO_H_
#define VREMENAR_WEATHERINFO_H_

#include <memory>

#include <QtPositioning/QGeoCoordinate>

#include "common/ListItem.h"
#include "weather/Weather.h"
#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

namespace Vremenar
{

class WeatherInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display NOTIFY updated)
    Q_PROPERTY(StationInfo *station READ station CONSTANT)
    Q_PROPERTY(WeatherCondition *condition READ condition NOTIFY updated)
public:
    enum Roles {
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

    [[nodiscard]] inline StationInfo *station() const { return _station.get(); }
    [[nodiscard]] inline WeatherCondition *condition() const { return _condition.get(); }

    void update(const WeatherInfo *source);

    static inline QHash<int, QByteArray> roleNames()
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
    std::unique_ptr<StationInfo> _station{};
    std::unique_ptr<WeatherCondition> _condition{};
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERINFO_H_
