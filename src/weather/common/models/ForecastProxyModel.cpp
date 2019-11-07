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

void ForecastProxyModel::setZoomLevel(qreal level)
{
    if (level != _zoomLevel) {
        _zoomLevel = level;
        invalidateFilter();
        Q_EMIT zoomLevelChanged();
    }
}

void ForecastProxyModel::setTime(qint64 time)
{
    if (time != _time) {
        _time = time;
        invalidateFilter();
        Q_EMIT timeChanged();
    }
}

bool ForecastProxyModel::filterAcceptsRow(int sourceRow,
                                          const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    bool name = index.data(ForecastEntry::DisplayRole).toString().contains(filterRegExp());
    bool zoomLevel = index.data(ForecastEntry::ZoomLevelRole).toReal() <= _zoomLevel;
    bool time = index.data(ForecastEntry::TimeRole).toLongLong() == _time;

    return name && zoomLevel && time;
}

} // namespace Vremenar
