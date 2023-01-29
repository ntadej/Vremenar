/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
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
#include "weather/models/WeatherAlertModel.h"

namespace Vremenar
{

class CurrentWeather : public QObject
{
    Q_OBJECT
public:
    explicit CurrentWeather(QObject *parent = nullptr);

    Q_PROPERTY(StationInfo *station READ station NOTIFY stationChanged)
    Q_PROPERTY(WeatherCondition *condition READ condition NOTIFY conditionChanged)

    void clear();

    [[nodiscard]] inline bool hasStation() const { return _station != nullptr; }

    void setStation(std::unique_ptr<StationInfo> station);
    [[nodiscard]] inline StationInfo *station() const { return _station.get(); }

    void updateCurrentWeather(std::unique_ptr<WeatherCondition> condition);
    [[nodiscard]] inline WeatherCondition *condition() const { return _condition.get(); }

    [[nodiscard]] inline WeatherAlertModel *alerts() const { return _alerts.get(); };

signals:
    void stationChanged(Vremenar::StationInfo *station);
    void conditionChanged(Vremenar::WeatherCondition *condition);

private:
    std::unique_ptr<StationInfo> _station{};
    std::unique_ptr<WeatherCondition> _condition{};
    std::unique_ptr<WeatherAlertModel> _alerts{};
};

} // namespace Vremenar

#endif // VREMENAR_CURRENTWEATHER_H_
