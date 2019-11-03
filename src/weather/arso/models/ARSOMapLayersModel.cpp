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
#include <QtPositioning/QGeoCoordinate>

#include "weather/arso/models/ARSOMapLayersModel.h"

#include "Config.h"

namespace Vremenar
{

ARSO::MapLayersModel::MapLayersModel(QObject *parent)
    : MapLayersModelBase(parent) {}

MapLayer *ARSO::MapLayersModel::createMapLayer(Weather::MapType type,
                                               const QJsonObject &data)
{
    QDateTime time = QDateTime::fromString(data[QStringLiteral("date")].toString(), QStringLiteral("yyyyMMddHHmm"));
    time.setTimeSpec(Qt::UTC);

    QUrl url(Vremenar::ARSOAPIResources + data[QStringLiteral("path")].toString());

    QStringList c = data[QStringLiteral("bbox")].toString().split(QStringLiteral(","));
    QGeoCoordinate topLeft(c[2].toDouble(), c[1].toDouble());
    QGeoCoordinate bottomRight(c[0].toDouble(), c[3].toDouble());
    QGeoRectangle range(topLeft, bottomRight);

    return appendRow(std::make_unique<MapLayer>(type, time, url, range));
}

void ARSO::MapLayersModel::addMapLayers(Weather::MapType type,
                                        const QJsonArray &data)
{
    if (type == Weather::ForecastMap) {
        for (const QJsonValue &value : data) {
            QJsonObject data = value.toObject();

            QDateTime time = QDateTime::fromString(data[QStringLiteral("date")].toString(), QStringLiteral("yyyyMMddHHmm"));
            time.setTimeSpec(Qt::UTC);
            QString url = data[QStringLiteral("path")].toString();

            appendRow(std::make_unique<MapLayer>(type, time, url));
        }
    } else {
        for (const QJsonValue &obj : data) {
            createMapLayer(type, obj.toObject());
        }
    }
}

} // namespace Vremenar
