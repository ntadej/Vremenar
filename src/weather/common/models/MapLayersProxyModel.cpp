/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/containers/MapLayer.h"

namespace Vremenar
{

MapLayersProxyModel::MapLayersProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      _time(0)
{
    connect(this, &MapLayersProxyModel::rowsInserted, this, &MapLayersProxyModel::rowCountChanged);
    connect(this, &MapLayersProxyModel::rowsRemoved, this, &MapLayersProxyModel::rowCountChanged);
}

void MapLayersProxyModel::setTime(const QDateTime &time)
{
    if (time.toSecsSinceEpoch() != _time) {
        _time = time.toSecsSinceEpoch();
        invalidateFilter();
        emit timestampChanged();
    }
}

void MapLayersProxyModel::setTimestamp(qint64 time)
{
    if (time != _time) {
        _time = time;
        invalidateFilter();
        emit timestampChanged();
    }
}

qint64 MapLayersProxyModel::minTimestamp() const
{
    if (!rowCount())
        return 0;

    return data(index(0, 0), MapLayer::TimeRole).toDateTime().toSecsSinceEpoch();
}

qint64 MapLayersProxyModel::maxTimestamp() const
{
    if (!rowCount())
        return 0;

    return data(index(rowCount() - 1, 0), MapLayer::TimeRole).toDateTime().toSecsSinceEpoch();
}

qint64 MapLayersProxyModel::stepTimestamp() const
{
    if (rowCount() < 2)
        return 0;

    qint64 first = data(index(0, 0), MapLayer::TimeRole).toDateTime().toSecsSinceEpoch();
    qint64 second = data(index(1, 0), MapLayer::TimeRole).toDateTime().toSecsSinceEpoch();

    return second - first;
}

bool MapLayersProxyModel::filterAcceptsRow(int sourceRow,
                                           const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    bool name = index.data(MapLayer::DisplayRole).toString().contains(filterRegExp());
    bool time = !_time || index.data(MapLayer::TimeRole).toDateTime().toSecsSinceEpoch() == _time;

    return name && time;
}

} // namespace Vremenar
