/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/arso/models/ARSOForecastModel.h"

namespace Vremenar
{

ARSO::ForecastModel::ForecastModel(QObject *parent)
    : ForecastModelBase(parent) {}

ForecastEntry *ARSO::ForecastModel::createEntry(const QJsonObject &data)
{
    QJsonObject properties = data[QStringLiteral("properties")].toObject();

    QString id = properties[QStringLiteral("id")].toString();
    QString title = properties[QStringLiteral("title")].toString();

    QJsonObject day = properties[QStringLiteral("days")].toArray()[0].toObject();
    QJsonObject timeline = day[QStringLiteral("timeline")].toArray()[0].toObject();

    QString icon = timeline[QStringLiteral("clouds_icon_wwsyn_icon")].toString();

    QJsonObject geometry = data[QStringLiteral("geometry")].toObject();
    QJsonArray coordinates = geometry[QStringLiteral("coordinates")].toArray();
    QGeoCoordinate coordinate{coordinates[0].toDouble(), coordinates[1].toDouble()};

    return appendRow(std::make_unique<ForecastEntry>(id, title, icon, coordinate));
}

void ARSO::ForecastModel::addEntries(const QJsonArray &data)
{
    for (const QJsonValue &obj : data) {
        createEntry(obj.toObject());
    }
}

} // namespace Vremenar
