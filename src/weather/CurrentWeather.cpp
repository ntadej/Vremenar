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

#include "weather/CurrentWeather.h"

#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"
#include "weather/models/WeatherAlertModel.h"

#include <QtCore/QObject>

#include <memory>
#include <utility>

namespace Vremenar
{

CurrentWeather::CurrentWeather(QObject *parent)
    : QObject(parent),
      _alerts(std::make_unique<WeatherAlertModel>(this))
{
}

void CurrentWeather::clear()
{
    _station.reset();
    _condition.reset();
    _alerts->clear();

    emit stationChanged(nullptr);
    emit conditionChanged(nullptr);
}

void CurrentWeather::setStation(std::unique_ptr<StationInfo> station)
{
    _station = std::move(station);

    if (_station != nullptr) {
        emit stationChanged(_station.get());
    } else {
        emit stationChanged(nullptr);
        emit conditionChanged(nullptr);
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
        emit conditionChanged(_condition.get());
    } else {
        emit conditionChanged(nullptr);
    }
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_CurrentWeather.cpp"
// NOLINTEND
