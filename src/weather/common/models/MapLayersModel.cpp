/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/models/MapLayersModel.h"

#include "common/Helpers.h"

namespace Vremenar
{

MapLayersModel::MapLayersModel(QObject *parent)
    : ListModel(std::make_unique<MapLayer>(), parent) {}

MapLayer *MapLayersModel::find(const QString &id) const
{
    return qobject_cast<MapLayer *>(ListModel::find(id));
}

MapLayer *MapLayersModel::row(int row)
{
    return qobject_cast<MapLayer *>(ListModel::row(row));
}

std::unique_ptr<MapLayer> MapLayersModel::takeRow(int row)
{
    return qobject_pointer_cast<MapLayer>(ListModel::takeRow(row).release());
}

void MapLayersModel::deleteMapLayer(MapLayer *genre)
{
    int r = indexFromItem(genre).row();
    removeRow(r);
}

} // namespace Vremenar
