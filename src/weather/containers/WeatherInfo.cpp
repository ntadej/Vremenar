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

#include "weather/containers/WeatherInfo.h"

namespace Vremenar
{

WeatherInfo::WeatherInfo(std::unique_ptr<StationInfo> station,
                         std::unique_ptr<WeatherCondition> condition,
                         QObject *parent)
    : ListItem(parent),
      _station(std::move(station)),
      _condition(std::move(condition))
{
    setId(_station->id());
}

QString WeatherInfo::display() const
{
    return _station->display();
}

QVariant WeatherInfo::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case StationRole:
        return QVariant::fromValue(station());
    case ConditionRole:
        return QVariant::fromValue(condition());
    }

    return QVariant();
}

void WeatherInfo::update(const WeatherInfo *source)
{
    if (source == nullptr) {
        return;
    }

    if (source->id() != id()) {
        return;
    }

    const WeatherCondition *c = source->condition();
    _condition = std::make_unique<WeatherCondition>(c->observation(),
                                                    c->time(),
                                                    c->icon(),
                                                    c->temperature(),
                                                    c->temperatureLow());

    Q_EMIT updated();
}

} // namespace Vremenar
