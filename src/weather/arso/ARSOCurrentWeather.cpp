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

#include "weather/arso/ARSOCurrentWeather.h"

namespace Vremenar
{

ARSO::CurrentWeather::CurrentWeather(QObject *parent)
    : CurrentWeatherBase(parent)
{
}

void ARSO::CurrentWeather::updateCurrentWeather(const QJsonObject &data)
{
    QJsonArray features = data[QStringLiteral("features")].toArray();

    for (QJsonValueRef obj : features) {
        QJsonObject properties = obj.toObject()[QStringLiteral("properties")].toObject();

        QString title = properties[QStringLiteral("title")].toString();
        if (title != location()) {
            continue;
        }

        QJsonObject day = properties[QStringLiteral("days")].toArray()[0].toObject();
        QJsonObject timeline = day[QStringLiteral("timeline")].toArray()[0].toObject();

        QDateTime time = QDateTime::fromString(timeline[QStringLiteral("valid")].toString(), Qt::ISODate);
        time.setTimeSpec(Qt::UTC);

        double temperature = timeline[QStringLiteral("t")].toString().toDouble();
        QString icon = timeline[QStringLiteral("clouds_icon_wwsyn_icon")].toString();

        setCurrentWeather(title, temperature, icon, time);
    }
}

} // namespace Vremenar
