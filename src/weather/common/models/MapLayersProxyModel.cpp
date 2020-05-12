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

#include "weather/common/containers/MapLayer.h"

#include "weather/common/models/MapLayersProxyModel.h"

namespace
{
constexpr int timerInterval{500};
constexpr int timerIntervalLong{750};
} // namespace

namespace Vremenar
{

MapLayersProxyModel::MapLayersProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      _timer(std::make_unique<QTimer>(this)),
      _url(QStringLiteral("qrc:/Vremenar/Maps/icons/blank.png"))
{
    connect(this, &MapLayersProxyModel::rowsInserted, this, &MapLayersProxyModel::rowCountChanged);
    connect(this, &MapLayersProxyModel::rowsRemoved, this, &MapLayersProxyModel::rowCountChanged);
    connect(this, &MapLayersProxyModel::rowCountChanged, this, &MapLayersProxyModel::setDefaultTimestamp);
    connect(_timer.get(), &QTimer::timeout, this, &MapLayersProxyModel::nextTimer);

    _timer->setInterval(timerInterval);
}

void MapLayersProxyModel::setUpdating(bool updating,
                                      bool silent)
{
    _updating = updating;

    if (!_updating && !silent) {
        Q_EMIT timestampChanged();
    }
}

void MapLayersProxyModel::setDefaultCoordinates(QVariant coordinates)
{
    _coordinates = std::move(coordinates);
}

qint64 MapLayersProxyModel::timestamp() const
{
    if (rowCount() == 0) {
        return 0;
    }

    return _time;
}

QString MapLayersProxyModel::day() const
{
    if (rowCount() == 0) {
        return QString();
    }

    auto current = QDateTime::currentDateTime();
    auto selected = QDateTime::fromMSecsSinceEpoch(_time);

    qint64 diff = current.daysTo(selected);
    if (diff == 0) {
        return QString();
    }
    if (diff == 1) {
        return tr("tomorrow");
    }
    if (diff == -1) {
        return tr("yesterday");
    }

    return selected.date().toString(Qt::SystemLocaleShortDate);
}

QString MapLayersProxyModel::title() const
{
    auto type = data(index(0, 0), MapLayer::TypeRole).value<Weather::MapType>();
    return Weather::mapTypeStringLocale(type);
}

void MapLayersProxyModel::setTimestamp(qint64 time)
{
    if (time != _time) {
        _time = time;

        for (int i = 0; i < rowCount(); i++) {
            const QModelIndex in = index(i, 0);
            if (data(in, MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch() == _time) {
                _url = data(in, MapLayer::UrlRole).toUrl().toString();
                if (_url.contains(QStringLiteral("json"))) {
                    _url = QString();
                }
                _coordinates = data(in, MapLayer::CoordinatesRole);
                _row = i;
                break;
            }
        }

        if (!_updating) {
            Q_EMIT timestampChanged();
        }
    }
}

void MapLayersProxyModel::setImage(const QString &image)
{
    if (_image != image) {
        _image = image;
        Q_EMIT imageChanged();
    }
}

void MapLayersProxyModel::setDefaultTimestamp()
{
    auto type = data(index(0, 0), MapLayer::TypeRole).value<Weather::MapType>();
    if (type == Weather::ForecastMap) {
        _timer->setInterval(timerIntervalLong);
        setTimestamp(data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());
        return;
    }

    _timer->setInterval(timerInterval);

    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
    qint64 newDefault{};
    for (int i = 0; i < rowCount(); i++) {
        const QModelIndex in = index(i, 0);
        qint64 candidate = data(in, MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
        if (candidate > now) {
            break;
        }
        newDefault = candidate;
    }
    setTimestamp(newDefault);
}

qint64 MapLayersProxyModel::minTimestamp() const
{
    if (rowCount() == 0) {
        return 0;
    }

    return data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
}

qint64 MapLayersProxyModel::maxTimestamp() const
{
    if (rowCount() == 0) {
        return 0;
    }

    return data(index(rowCount() - 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
}

void MapLayersProxyModel::previous()
{
    if (_row > 0) {
        setTimestamp(data(index(_row - 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());

        if (_animated) {
            _timer->stop();
            _animated = false;
            Q_EMIT animatedChanged();
        }
    }
}

void MapLayersProxyModel::next()
{
    if (_row < rowCount() - 1) {
        setTimestamp(data(index(_row + 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());

        if (_animated) {
            _timer->stop();
            _animated = false;
            Q_EMIT animatedChanged();
        }
    }
}

void MapLayersProxyModel::nextTimer()
{
    _timer->stop();

    if (_row == rowCount() - 1) {
        setTimestamp(data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());
    } else {
        setTimestamp(data(index(_row + 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());
    }
}

void MapLayersProxyModel::play()
{
    if (_animated) {
        _timer->stop();
        _animated = false;
    } else {
        _timer->start();
        _animated = true;
    }

    Q_EMIT animatedChanged();
}

void MapLayersProxyModel::playResume()
{
    if (_animated) {
        _timer->start();
    }
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
