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
#include <QtCore/QTimeZone>
#include <QtPositioning/QGeoCoordinate>

#include "weather/backend/Common.h"
#include "weather/backend/models/MapLayersModel.h"

#include "Config.h"

namespace Vremenar
{

Backend::MapLayersModel::MapLayersModel(QObject *parent)
    : MapLayersModelBase(parent) {}

MapLayer *Backend::MapLayersModel::createMapLayer(Weather::MapType type,
                                                  Weather::MapRenderingType rendering,
                                                  const QJsonObject &data,
                                                  const QGeoRectangle &bbox)
{
    QDateTime time = QDateTime::fromMSecsSinceEpoch(data[QStringLiteral("timestamp")].toString().toULongLong());
    QUrl url(data[QStringLiteral("url")].toString());
    auto observation = Weather::observationTypeFromString(data[QStringLiteral("observation")].toString());

    return appendRow(std::make_unique<MapLayer>(type, rendering, observation, time, url, bbox));
}

void Backend::MapLayersModel::addMapLayers(Weather::MapType type,
                                           const QJsonObject &data)
{
    auto rendering = Weather::mapRenderingTypeFromString(data[QStringLiteral("rendering")].toString());

    // bbox
    QGeoRectangle bbox;
    if (data.contains(QStringLiteral("bbox"))) {
        QJsonArray c = data[QStringLiteral("bbox")].toArray();
        QGeoCoordinate topLeft(c[2].toDouble(), c[1].toDouble());
        QGeoCoordinate bottomRight(c[0].toDouble(), c[3].toDouble());
        bbox = QGeoRectangle(topLeft, bottomRight);
    }

    QJsonArray layers = data[QStringLiteral("layers")].toArray();
    for (const QJsonValueRef &obj : layers) {
        createMapLayer(type, rendering, obj.toObject(), bbox);
    }
}

} // namespace Vremenar
