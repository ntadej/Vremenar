/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/common/containers/WeatherInfo.h"

#include "weather/common/models/WeatherMapProxyModel.h"

namespace Vremenar
{

WeatherMapProxyModel::WeatherMapProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    connect(this, &WeatherMapProxyModel::rowsInserted, this, &WeatherMapProxyModel::rowCountChanged);
    connect(this, &WeatherMapProxyModel::rowsRemoved, this, &WeatherMapProxyModel::rowCountChanged);
}

void WeatherMapProxyModel::setZoomLevel(qreal level)
{
    if (level != _zoomLevel) {
        _zoomLevel = level;
        invalidateFilter();
        Q_EMIT zoomLevelChanged();
    }
}

void WeatherMapProxyModel::setTime(qint64 time)
{
    if (time != _time) {
        _time = time;
        invalidateFilter();
        Q_EMIT timeChanged();
    }
}

bool WeatherMapProxyModel::filterAcceptsRow(int sourceRow,
                                            const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    bool name = index.data(WeatherInfo::DisplayRole).toString().contains(filterRegExp());
    bool zoomLevel = index.data(WeatherInfo::ZoomLevelRole).toReal() <= _zoomLevel;
    bool time = _time == 0 || index.data(WeatherInfo::TimeRole).toLongLong() == _time;

    return name && zoomLevel && time;
}

} // namespace Vremenar
