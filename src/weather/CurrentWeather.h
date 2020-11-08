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

#ifndef VREMENAR_CURRENTWEATHER_H_
#define VREMENAR_CURRENTWEATHER_H_

#include <memory>

#include <QtCore/QDateTime>
#include <QtCore/QObject>

#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

namespace Vremenar
{

class CurrentWeather : public QObject
{
    Q_OBJECT
public:
    explicit CurrentWeather(QObject *parent = nullptr);
    virtual ~CurrentWeather() = default;

    Q_PROPERTY(StationInfo *station READ station NOTIFY weatherChanged)
    Q_PROPERTY(WeatherCondition *condition READ condition NOTIFY weatherChanged)

    [[nodiscard]] inline bool hasStation() const { return _station != nullptr; }

    void setStation(std::unique_ptr<StationInfo> station);
    [[nodiscard]] inline StationInfo *station() const { return _station.get(); }

    void updateCurrentWeather(std::unique_ptr<WeatherCondition> condition);
    [[nodiscard]] inline WeatherCondition *condition() const { return _condition.get(); }

Q_SIGNALS:
    void weatherChanged(const StationInfo *station,
                        const WeatherCondition *condition);

private:
    std::unique_ptr<StationInfo> _station{};
    std::unique_ptr<WeatherCondition> _condition{};
};

} // namespace Vremenar

#endif // VREMENAR_CURRENTWEATHER_H_
