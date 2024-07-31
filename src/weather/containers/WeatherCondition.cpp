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

#include "weather/containers/WeatherCondition.h"

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <memory>
#include <utility>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

WeatherCondition::WeatherCondition(Weather::ObservationType observation,
                                   qint64 time,
                                   QString icon,
                                   qreal temperature,
                                   qreal temperatureLow,
                                   QObject *parent)
    : ListItem(parent),
      _observation(observation),
      _time(time),
      _icon(std::move(icon)),
      _temperature(temperature),
      _temperatureLow(temperatureLow)
{
    setId(QString::number(_time));
}

std::unique_ptr<WeatherCondition> WeatherCondition::fromJson(const QJsonObject &json)
{
    const Weather::ObservationType observation = Weather::observationTypeFromString(json["observation"_L1].toString());
    const QDateTime time = QDateTime::fromMSecsSinceEpoch(json["timestamp"_L1].toString().toLongLong());
    const QString icon = json["icon"_L1].toString();

    double temperature{};
    double temperatureLow{-1000}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    if (json.contains("temperature_low"_L1) && !json["temperature_low"_L1].isNull()) {
        temperature = json["temperature"_L1].toDouble();
        temperatureLow = json["temperature_low"_L1].toDouble();
    } else {
        temperature = json["temperature"_L1].toDouble();
    }

    return std::make_unique<WeatherCondition>(observation, time.toMSecsSinceEpoch(), icon, temperature, temperatureLow);
}

QString WeatherCondition::display() const
{
    return displayTemperature();
}

QString WeatherCondition::displayTemperature() const
{
    return u"%1 °C"_s.arg(_temperature);
}

QString WeatherCondition::displayTemperatureShort() const
{
    return u"%1°"_s.arg(_temperature);
}

QVariant WeatherCondition::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case ObservationRole:
        return observation();
    case TimeRole:
        return time();
    case IconRole:
        return icon();
    case TemperatureRole:
        return temperature();
    case TemperatureLowRole:
        return temperatureLow();
    case DisplayTemperatureRole:
        return displayTemperature();
    case DisplayTemperatureShortRole:
        return displayTemperatureShort();
    default:
        return {};
    }

    return {};
}

void WeatherCondition::update(const WeatherCondition *source)
{
    if (source == nullptr) {
        return;
    }

    _icon = source->icon();
    _temperature = source->temperature();
    _temperatureLow = source->temperatureLow();

    emit updated();
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_WeatherCondition.cpp"
// NOLINTEND
