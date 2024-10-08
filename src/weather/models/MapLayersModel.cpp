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

#include "weather/models/MapLayersModel.h"

#include "common/ListModel.h"
#include "weather/Weather.h"
#include "weather/containers/MapLayer.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QTimeZone>
#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoRectangle>

#include <memory>

using Qt::Literals::StringLiterals::operator""_L1;

namespace Vremenar
{

MapLayersModel::MapLayersModel(QObject *parent)
    : ListModel(MapLayer::roleNames(), parent) {}

MapLayer *MapLayersModel::createMapLayer(Weather::Source source,
                                         Weather::MapType type,
                                         Weather::MapRenderingType rendering,
                                         const QJsonObject &data,
                                         const QGeoRectangle &bbox)
{
    const QDateTime time = QDateTime::fromMSecsSinceEpoch(data["timestamp"_L1].toString().toLongLong());
    const QString url = data["url"_L1].toString();
    const auto observation = Weather::observationTypeFromString(data["observation"_L1].toString());

    return appendRow(std::make_unique<MapLayer>(source, type, rendering, observation, time, url, bbox));
}

void MapLayersModel::addMapLayers(Weather::Source source,
                                  Weather::MapType type,
                                  const QJsonObject &data)
{
    auto rendering = Weather::mapRenderingTypeFromString(data["rendering"_L1].toString());
    if (rendering == Weather::MapRenderingType::UnknownRendering) {
        return;
    }

    // bbox
    QGeoRectangle bbox;
    if (data.contains("bbox"_L1)) {
        QJsonArray c = data["bbox"_L1].toArray();
        if (!c.empty()) {
            const QGeoCoordinate topLeft(c[2].toDouble(), c[1].toDouble());
            const QGeoCoordinate bottomRight(c[0].toDouble(), c[3].toDouble());
            bbox = QGeoRectangle(topLeft, bottomRight);
        }
    }

    const QJsonArray layers = data["layers"_L1].toArray();
    for (const auto &obj : layers) {
        createMapLayer(source, type, rendering, obj.toObject(), bbox);
    }
}

MapLayer *MapLayersModel::findLayer(Weather::MapType type,
                                    qint64 time) const
{
    return find<MapLayer>(Weather::mapTypeToString(type) + "_" + QString::number(time));
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_MapLayersModel.cpp"
// NOLINTEND
