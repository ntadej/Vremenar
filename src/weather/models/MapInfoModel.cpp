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

#include "weather/models/MapInfoModel.h"

#include "common/ListModel.h"
#include "weather/Weather.h"
#include "weather/containers/MapInfo.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>

#include <cstddef>
#include <memory>
#include <vector>

using Qt::Literals::StringLiterals::operator""_L1;

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
        const auto mapType = Weather::mapTypeFromString(typeInfo["map_type"_L1].toString());
        // backward compatibility
        const QString renderingTypeString
            = typeInfo.contains("rendering_type"_L1)
                  ? typeInfo["rendering_type"_L1].toString()
                  : typeInfo["rendering"_L1].toString();
        const auto renderingType = Weather::mapRenderingTypeFromString(renderingTypeString);
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
    l.reserve(static_cast<std::size_t>(rowCount()));
    for (int i = 0; i < rowCount(); i++) {
        l.push_back(row<MapInfo>(i)->type());
    }
    return l;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_MapInfoModel.cpp"
// NOLINTEND
