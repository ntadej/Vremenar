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

#include "weather/containers/WeatherCondition.h"

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
    Weather::ObservationType observation = Weather::observationTypeFromString(json[QStringLiteral("observation")].toString());
    QDateTime time = QDateTime::fromMSecsSinceEpoch(json[QStringLiteral("timestamp")].toString().toULongLong());
    QString icon = json[QStringLiteral("icon")].toString();

    double temperature{};
    double temperatureLow{-1000}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    if (json.contains(QStringLiteral("temperature_low")) && !json[QStringLiteral("temperature_low")].isNull()) {
        temperature = json[QStringLiteral("temperature")].toDouble();
        temperatureLow = json[QStringLiteral("temperature_low")].toDouble();
    } else {
        temperature = json[QStringLiteral("temperature")].toDouble();
    }

    return std::make_unique<WeatherCondition>(observation, time.toMSecsSinceEpoch(), icon, temperature, temperatureLow);
}

QString WeatherCondition::display() const
{
    return displayTemperature();
}

QString WeatherCondition::displayTemperature() const
{
    return QStringLiteral("%1 °C").arg(_temperature);
}

QString WeatherCondition::displayTemperatureShort() const
{
    return QStringLiteral("%1°").arg(_temperature);
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
    }

    return QVariant();
}

void WeatherCondition::update(const WeatherCondition *source)
{
    if (source == nullptr) {
        return;
    }

    _icon = source->icon();
    _temperature = source->temperature();
    _temperatureLow = source->temperatureLow();

    Q_EMIT updated();
}

} // namespace Vremenar
