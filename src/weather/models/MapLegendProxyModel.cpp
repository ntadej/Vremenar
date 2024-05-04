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

#include "weather/models/MapLegendProxyModel.h"

#include "weather/Weather.h"
#include "weather/containers/MapLegendItem.h"

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/QSortFilterProxyModel>

#include <cmath>

namespace Vremenar
{

MapLegendProxyModel::MapLegendProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    connect(this, &MapLegendProxyModel::rowsInserted, this, &MapLegendProxyModel::rowCountChanged);
    connect(this, &MapLegendProxyModel::rowsRemoved, this, &MapLegendProxyModel::rowCountChanged);
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
    if (textBased()) {
        return false;
    }

    for (int i{}; i < rowCount(); i++) {
        if (index(i, 0).data(MapLegendItem::PlaceholderRole).toBool()) {
            continue;
        }

        const float value = index(i, 0).data(MapLegendItem::DisplayRole).toString().toFloat();
        if (std::fmod(value, 1.F) != 0.F) {
            return true;
        }
    }

    return false;
}

bool MapLegendProxyModel::textBased() const
{
    return _type == Weather::HailProbabilityMap;
}

bool MapLegendProxyModel::filterAcceptsRow(int sourceRow,
                                           const QModelIndex &sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    // const bool name = index.data(MapLegendItem::DisplayRole).toString().contains(filterRegExp());
    const bool type = static_cast<Weather::MapType>(index.data(MapLegendItem::TypeRole).toInt()) == _type;

    return type;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_MapLegendProxyModel.cpp"
// NOLINTEND
