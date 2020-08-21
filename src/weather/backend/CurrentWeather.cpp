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

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/backend/CurrentWeather.h"

namespace Vremenar
{

Backend::CurrentWeather::CurrentWeather(QObject *parent)
    : CurrentWeatherBase(parent)
{
}

void Backend::CurrentWeather::updateCurrentWeather(const QJsonArray &data)
{
    for (const QJsonValue &feature : data) {
        QJsonObject obj = feature.toObject();

        QString title = obj[QStringLiteral("title")].toString();
        if (title != location()) {
            continue;
        }

        QDateTime time = QDateTime::fromMSecsSinceEpoch(obj[QStringLiteral("timestamp")].toString().toULongLong());
        QString icon = obj[QStringLiteral("icon")].toString();
        double temperature = obj[QStringLiteral("temperature")].toDouble();

        setCurrentWeather(title, temperature, icon, time);
    }
}

} // namespace Vremenar
