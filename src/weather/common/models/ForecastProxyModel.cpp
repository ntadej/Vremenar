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

#include "weather/common/containers/ForecastEntry.h"

#include "weather/common/models/ForecastProxyModel.h"

namespace Vremenar
{

ForecastProxyModel::ForecastProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    connect(this, &ForecastProxyModel::rowsInserted, this, &ForecastProxyModel::rowCountChanged);
    connect(this, &ForecastProxyModel::rowsRemoved, this, &ForecastProxyModel::rowCountChanged);
}

bool ForecastProxyModel::filterAcceptsRow(int sourceRow,
                                          const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    bool name = index.data(ForecastEntry::DisplayRole).toString().contains(filterRegExp());
    // bool time = !_time || index.data(MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch() == _time;

    return name;
}

} // namespace Vremenar
