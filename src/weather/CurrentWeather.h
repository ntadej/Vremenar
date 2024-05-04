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

#ifndef VREMENAR_CURRENTWEATHER_H_
#define VREMENAR_CURRENTWEATHER_H_

#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

#include <QtCore/QDateTime>
#include <QtCore/QObject>

#include <memory>

namespace Vremenar
{

class WeatherAlertModel;

class CurrentWeather : public QObject
{
    Q_OBJECT
public:
    explicit CurrentWeather(QObject *parent = nullptr);

    Q_PROPERTY(StationInfo *station READ station NOTIFY stationChanged)
    Q_PROPERTY(WeatherCondition *condition READ condition NOTIFY conditionChanged)

    void clear();

    [[nodiscard]] bool hasStation() const { return _station != nullptr; }

    void setStation(std::unique_ptr<StationInfo> station);
    [[nodiscard]] StationInfo *station() const { return _station.get(); }

    void updateCurrentWeather(std::unique_ptr<WeatherCondition> condition);
    [[nodiscard]] WeatherCondition *condition() const { return _condition.get(); }

    [[nodiscard]] WeatherAlertModel *alerts() const { return _alerts.get(); };

signals:
    void stationChanged(Vremenar::StationInfo *station);          // NOLINT(readability-inconsistent-declaration-parameter-name)
    void conditionChanged(Vremenar::WeatherCondition *condition); // NOLINT(readability-inconsistent-declaration-parameter-name)

private:
    std::unique_ptr<StationInfo> _station;
    std::unique_ptr<WeatherCondition> _condition;
    std::unique_ptr<WeatherAlertModel> _alerts;
};

} // namespace Vremenar

#endif // VREMENAR_CURRENTWEATHER_H_
