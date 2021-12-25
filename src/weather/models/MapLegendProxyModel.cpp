/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/models/MapLegendProxyModel.h"
#include "weather/containers/MapLegendItem.h"

namespace Vremenar
{

MapLegendProxyModel::MapLegendProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void MapLegendProxyModel::setType(Weather::MapType type)
{
    if (type != _type) {
        _type = type;
        invalidateFilter();
        emit typeChanged();
    }
}

bool MapLegendProxyModel::wide() const
{
    return _type == Weather::UVDoseMap;
}

bool MapLegendProxyModel::textBased() const
{
    return _type == Weather::HailProbabilityMap;
}

bool MapLegendProxyModel::filterAcceptsRow(int sourceRow,
                                           const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    // bool name = index.data(MapLegendItem::DisplayRole).toString().contains(filterRegExp());
    bool type = Weather::MapType(index.data(MapLegendItem::TypeRole).toInt()) == _type;

    return type;
}

} // namespace Vremenar
