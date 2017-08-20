/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/containers/MapLayer.h"
#include "weather/common/models/MapLayersProxyModel.h"

MapLayersProxyModel::MapLayersProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      _type(Vremenar::Weather::PrecipitationMap) {}

MapLayersProxyModel::~MapLayersProxyModel() {}

void MapLayersProxyModel::setType(Vremenar::Weather::MapType type)
{
    if (type != _type) {
        _type = type;
        invalidateFilter();
    }
}

bool MapLayersProxyModel::filterAcceptsRow(int sourceRow,
                                           const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    bool name = index.data(MapLayer::DisplayRole).toString().contains(filterRegExp());
    bool type = index.data(MapLayer::TypeRole).toInt() == _type;

    return name && type;
}
