/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/models/StationListProxyModel.h"
#include "weather/containers/StationInfo.h"

namespace Vremenar
{

StationListProxyModel::StationListProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void StationListProxyModel::setIgnoreForecastOnly(bool ignoreForecastOnly)
{
    if (ignoreForecastOnly != _ignoreForecastOnly) {
        _ignoreForecastOnly = ignoreForecastOnly;
        invalidateFilter();
        emit ignoreForecastOnlyChanged();
    }
}

bool StationListProxyModel::filterAcceptsRow(int sourceRow,
                                             const QModelIndex &sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    const bool name = index.data(StationInfo::DisplayRole).toString().contains(filterRegularExpression());
    bool forecastStatus{true};
    if (_ignoreForecastOnly) {
        forecastStatus = !index.data(StationInfo::ForecastOnlyRole).toBool();
    }

    return name && forecastStatus;
}

} // namespace Vremenar

#include "moc_StationListProxyModel.cpp"
