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

#include "weather/CurrentWeather.h"

namespace Vremenar
{

CurrentWeather::CurrentWeather(QObject *parent)
    : QObject(parent)
{
}

void CurrentWeather::setStation(std::unique_ptr<StationInfo> station)
{
    _station = std::move(station);

    if (_station != nullptr) {
        Q_EMIT stationChanged(_station.get());
    } else {
        Q_EMIT stationChanged(nullptr);
        Q_EMIT conditionChanged(nullptr);
    }
}

void CurrentWeather::updateCurrentWeather(std::unique_ptr<WeatherCondition> condition)
{
    if (_condition == nullptr) {
        _condition = std::move(condition);
    } else {
        _condition->update(condition.get());
    }

    if (_station != nullptr && _condition != nullptr) {
        Q_EMIT conditionChanged(_condition.get());
    } else {
        Q_EMIT conditionChanged(nullptr);
    }
}

} // namespace Vremenar
