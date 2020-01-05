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

#include "weather/common/CurrentWeatherBase.h"

namespace Vremenar
{

CurrentWeatherBase::CurrentWeatherBase(QObject *parent)
    : QObject(parent)
{
}

QString CurrentWeatherBase::temperature() const
{
    return QStringLiteral("%1 °C").arg(_temperature);
}

QString CurrentWeatherBase::temperatureShort() const
{
    return QStringLiteral("%1°").arg(_temperature);
}

void CurrentWeatherBase::setCurrentWeather(const QString &location,
                                           double temperature,
                                           const QString &icon,
                                           const QDateTime &time)
{
    _location = location;
    _temperature = temperature;
    _icon = icon;
    _time = time;

    Q_EMIT weatherChanged();
}

} // namespace Vremenar
