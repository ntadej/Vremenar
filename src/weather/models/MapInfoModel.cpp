/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/models/MapInfoModel.h"

namespace Vremenar
{

MapInfoModel::MapInfoModel(QObject *parent)
    : ListModel(MapInfo::roleNames(), parent) {}

void MapInfoModel::generateModel(const std::vector<Weather::MapType> &supported)
{
    for (const Weather::MapType type : supported) {
        if (type == Weather::MapType::UnknownMapType) {
            continue;
        }
        appendRow(std::make_unique<MapInfo>(type));
    }
}

void MapInfoModel::generateModel(const QJsonArray &supported)
{
    for (const auto &typeInfoRef : supported) {
        const QJsonObject typeInfo = typeInfoRef.toObject();
        const auto mapType = Weather::mapTypeFromString(typeInfo[QStringLiteral("map_type")].toString());
        const auto renderingType = Weather::mapRenderingTypeFromString(typeInfo[QStringLiteral("rendering")].toString());
        if (mapType == Weather::MapType::UnknownMapType || renderingType == Weather::MapRenderingType::UnknownRendering) {
            continue;
        }
        appendRow(std::make_unique<MapInfo>(mapType));
    }
}

QStringList MapInfoModel::list() const
{
    QStringList l;
    l.reserve(rowCount());
    for (int i = 0; i < rowCount(); i++) {
        l << row<MapInfo>(i)->display();
    }
    return l;
}

std::vector<Weather::MapType> MapInfoModel::types() const
{
    std::vector<Weather::MapType> l;
    l.reserve(static_cast<size_t>(rowCount()));
    for (int i = 0; i < rowCount(); i++) {
        l.push_back(row<MapInfo>(i)->type());
    }
    return l;
}

} // namespace Vremenar

#include "moc_MapInfoModel.cpp"
