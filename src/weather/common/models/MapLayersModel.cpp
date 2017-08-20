/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/models/MapLayersModel.h"

MapLayersModel::MapLayersModel(QObject *parent)
    : ListModel(new MapLayer, parent) {}

MapLayersModel::~MapLayersModel() {}

MapLayer *MapLayersModel::find(const QString &id) const
{
    return qobject_cast<MapLayer *>(ListModel::find(id));
}

MapLayer *MapLayersModel::row(int row)
{
    return qobject_cast<MapLayer *>(ListModel::row(row));
}

MapLayer *MapLayersModel::takeRow(int row)
{
    return qobject_cast<MapLayer *>(ListModel::takeRow(row));
}

void MapLayersModel::deleteMapLayer(MapLayer *genre)
{
    int r = indexFromItem(genre).row();
    removeRow(r);
}
