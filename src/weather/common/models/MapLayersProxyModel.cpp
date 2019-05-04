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

namespace Vremenar
{

MapLayersProxyModel::MapLayersProxyModel(QVariant defaultCoordinates,
                                         QObject *parent)
    : QSortFilterProxyModel(parent),
      _time(0),
      _coordinates(defaultCoordinates)
{
    connect(this, &MapLayersProxyModel::rowsInserted, this, &MapLayersProxyModel::rowCountChanged);
    connect(this, &MapLayersProxyModel::rowsRemoved, this, &MapLayersProxyModel::rowCountChanged);
}

void MapLayersProxyModel::setTimestamp(qint64 time)
{
    if (time != _time) {
        _time = time;

        for (int i = 0; i < rowCount(); i++) {
            const QModelIndex in = index(i, 0);
            if (data(in, MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch() == _time) {
                _url = data(in, MapLayer::UrlRole).toUrl().toString();
                _coordinates = data(in, MapLayer::CoordinatesRole);
                break;
            }
        }

        emit timestampChanged();
    }
}

qint64 MapLayersProxyModel::minTimestamp() const
{
    if (!rowCount())
        return 0;

    return data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
}

qint64 MapLayersProxyModel::maxTimestamp() const
{
    if (!rowCount())
        return 0;

    return data(index(rowCount() - 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
}

qint64 MapLayersProxyModel::stepTimestamp() const
{
    if (rowCount() < 2)
        return 0;

    qint64 first = data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
    qint64 second = data(index(1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();

    return second - first;
}

bool MapLayersProxyModel::filterAcceptsRow(int sourceRow,
                                           const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    bool name = index.data(MapLayer::DisplayRole).toString().contains(filterRegExp());
    // bool time = !_time || index.data(MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch() == _time;

    return name;
}

} // namespace Vremenar
