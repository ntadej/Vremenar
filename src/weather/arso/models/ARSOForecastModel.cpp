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

#include <QtCore/QDateTime>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/arso/ARSOCommon.h"
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

    QDateTime time = QDateTime::fromString(timeline[QStringLiteral("valid")].toString(), Qt::ISODate);
    time.setTimeSpec(Qt::UTC);

    QString icon = timeline[QStringLiteral("clouds_icon_wwsyn_icon")].toString();

    QJsonObject geometry = data[QStringLiteral("geometry")].toObject();
    QJsonArray coordinates = geometry[QStringLiteral("coordinates")].toArray();
    QGeoCoordinate coordinate{coordinates[1].toDouble(), coordinates[0].toDouble()};

    qreal zoomLevel = properties[QStringLiteral("zoomLevel")].toString().toDouble();
    qreal epsilon = 0.25; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    zoomLevel = zoomLevel == 5 ? zoomLevel + 1 : zoomLevel; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    zoomLevel /= 6;                                         // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    zoomLevel *= ARSO::maxZoomLevel - ARSO::minZoomLevel - epsilon;
    zoomLevel = ARSO::maxZoomLevel - zoomLevel - epsilon;

    return appendRow(std::make_unique<ForecastEntry>(id, time.toMSecsSinceEpoch(), title, icon, coordinate, zoomLevel));
}

void ARSO::ForecastModel::addEntries(const QJsonArray &data)
{
    for (const QJsonValue &obj : data) {
        createEntry(obj.toObject());
    }
}

} // namespace Vremenar
