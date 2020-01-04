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

#include "weather/common/models/MapInfoModel.h"

namespace Vremenar
{

MapInfoModel::MapInfoModel(QObject *parent)
    : ListModel(MapInfo::roleNames(), parent) {}

void MapInfoModel::generateModel(const std::vector<Weather::MapType> &supported)
{
    for (Weather::MapType type : supported) {
        appendRow(std::make_unique<MapInfo>(type));
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

} // namespace Vremenar
