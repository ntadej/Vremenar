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

#include "weather/common/containers/WeatherInfo.h"

namespace Vremenar
{

WeatherInfo::WeatherInfo(const QString &id,
                         Weather::ObservationType observation,
                         qint64 time,
                         QString title,
                         QString icon,
                         qreal temperature,
                         qreal temperatureLow,
                         const QGeoCoordinate &coordinate,
                         qreal zoomLevel,
                         QObject *parent)
    : ListItem(parent),
      _observation(observation),
      _time(time),
      _title(std::move(title)),
      _icon(std::move(icon)),
      _temperature(temperature),
      _temperatureLow(temperatureLow),
      _coordinate(coordinate),
      _zoomLevel(zoomLevel)
{
    setId(id);
}

QString WeatherInfo::display() const
{
    return _title;
}

QVariant WeatherInfo::data(int role) const
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
    case CoordinateRole:
        return QVariant::fromValue(coordinate());
    case ZoomLevelRole:
        return zoomLevel();
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

    _title = source->display();
    _icon = source->icon();
    _temperature = source->temperature();
    _temperatureLow = source->temperatureLow();

    Q_EMIT updated();
}

} // namespace Vremenar
