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

#include "weather/models/WeatherMapProxyModel.h"

#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"
#include "weather/containers/WeatherInfo.h"

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QTimer>
#include <QtPositioning/QGeoShape>

#include <memory>

namespace
{
constexpr int updateInterval{100};
} // namespace

namespace Vremenar
{

WeatherMapProxyModel::WeatherMapProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      _timer(std::make_unique<QTimer>(this))
{
    _timer->setInterval(updateInterval);
    _timer->setSingleShot(true);

    connect(this, &WeatherMapProxyModel::rowsInserted, this, &WeatherMapProxyModel::rowCountChanged);
    connect(this, &WeatherMapProxyModel::rowsRemoved, this, &WeatherMapProxyModel::rowCountChanged);

    connect(_timer.get(), &QTimer::timeout, this, &WeatherMapProxyModel::invalidateFilter);
}

void WeatherMapProxyModel::setZoomLevel(qreal level)
{
    if (level != _zoomLevel) {
        _timer->stop();

        _zoomLevel = level;

        emit zoomLevelChanged();

        _timer->start();
    }
}

void WeatherMapProxyModel::setVisibleRegion(const QGeoShape &shape)
{
    if (shape != _visibleRegion) {
        _timer->stop();

        _visibleRegion = shape;

        emit visibleRegionChanged();

        _timer->start();
    }
}

void WeatherMapProxyModel::setTime(qint64 time)
{
    if (time != _time) {
        _timer->stop();

        _time = time;
        invalidateFilter();
        emit timeChanged();
    }
}

bool WeatherMapProxyModel::filterAcceptsRow(int sourceRow,
                                            const QModelIndex &sourceParent) const
{
    _timer->stop();

    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    const bool name = index.data(WeatherInfo::DisplayRole).toString().contains(filterRegularExpression());

    const StationInfo *station = index.data(WeatherInfo::StationRole).value<StationInfo *>();
    const WeatherCondition *condition = index.data(WeatherInfo::ConditionRole).value<WeatherCondition *>();

    const bool zoomLevel = station->zoomLevel() <= _zoomLevel;
    const bool visibleRegion = _visibleRegion.contains(station->coordinate());
    const bool time = _time == 0 || condition->time() == _time;

    return name && zoomLevel && visibleRegion && time;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_WeatherMapProxyModel.cpp"
// NOLINTEND
