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

#include <QtCore/QLocale>

#include "weather/containers/MapLayer.h"

#include "weather/models/MapLayersProxyModel.h"

namespace
{
constexpr int timerInterval{500};
constexpr int timerIntervalLong{750};
} // namespace

namespace Vremenar
{

MapLayersProxyModel::MapLayersProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      _timer(std::make_unique<QTimer>(this))
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
        emit timestampChanged();
        emit mapChanged(_type, _renderingType, _urlPrevious, _urlCurrent, _urlNext);
    }
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
        return {};
    }

    if (_timeDefault == _time) {
        return tr("recent");
    }

    auto current = QDateTime::currentDateTime();
    auto selected = QDateTime::fromMSecsSinceEpoch(_time);

    qint64 diff = current.daysTo(selected);
    if (diff == 0) {
        if (_time > _timeDefault) {
            return tr("forecast");
        }
        return {};
    }
    if (diff == 1) {
        return tr("tomorrow");
    }
    if (diff == -1) {
        return tr("yesterday");
    }

    return QLocale::system().toString(selected.date(), QLocale::ShortFormat);
}

bool MapLayersProxyModel::dayHighlighted() const
{
    return _timeDefault == _time;
}

QString MapLayersProxyModel::title() const
{
    auto type = data(index(0, 0), MapLayer::TypeRole).value<Weather::MapType>();
    return Weather::mapTypeToLocalizedString(type);
}

void MapLayersProxyModel::setTimestamp(qint64 time)
{
    if (time != _time) {
        _time = time;

        for (int i = 0; i < rowCount(); i++) {
            const QModelIndex in = index(i, 0);
            if (data(in, MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch() == _time) {
                _type = Weather::MapType(data(in, MapLayer::TypeRole).toInt());
                _renderingType = Weather::MapRenderingType(data(in, MapLayer::RenderingRole).toInt());
                _urlCurrent = data(in, MapLayer::UrlRole).toUrl().toString();
                if (_urlCurrent.contains(QStringLiteral("json"))) {
                    _urlPrevious = QString();
                    _urlCurrent = QString();
                    _urlNext = QString();
                } else {
                    if (i > 0) {
                        _urlPrevious = data(index(i - 1, 0), MapLayer::UrlRole).toUrl().toString();
                    } else {
                        _urlPrevious = data(index(rowCount() - 1, 0), MapLayer::UrlRole).toUrl().toString();
                    }
                    if (i + 1 < rowCount()) {
                        _urlNext = data(index(i + 1, 0), MapLayer::UrlRole).toUrl().toString();
                    } else {
                        _urlNext = data(index(0, 0), MapLayer::UrlRole).toUrl().toString();
                    }
                }
                _coordinates = data(in, MapLayer::CoordinatesRole);
                _row = i;
                break;
            }
        }

        if (!_updating) {
            emit timestampChanged();
            emit mapChanged(_type, _renderingType, _urlPrevious, _urlCurrent, _urlNext);
        }
    }
}

void MapLayersProxyModel::setDefaultTimestamp()
{
    auto type = data(index(0, 0), MapLayer::TypeRole).value<Weather::MapType>();
    if (type == Weather::WeatherConditionMap) {
        _timeDefault = data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
        _timer->setInterval(timerIntervalLong);
        setTimestamp(_timeDefault);
        return;
    }

    _timer->setInterval(timerInterval);

    qint64 newDefault{};
    for (int i = 0; i < rowCount(); i++) {
        const QModelIndex in = index(i, 0);
        auto observation = data(in, MapLayer::ObservationRole).value<Weather::ObservationType>();
        if (observation == Weather::Recent) {
            newDefault = data(in, MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
            break;
        }
    }
    _timeDefault = newDefault;
    setTimestamp(_timeDefault);
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

void MapLayersProxyModel::first()
{
    if (_row > 0) {
        setTimestamp(data(index(0, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());

        if (_animated) {
            _timer->stop();
            _animated = false;
            emit animatedChanged();
        }
    }
}

void MapLayersProxyModel::previous()
{
    if (_row > 0) {
        setTimestamp(data(index(_row - 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());

        if (_animated) {
            _timer->stop();
            _animated = false;
            emit animatedChanged();
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
            emit animatedChanged();
        }
    }
}

void MapLayersProxyModel::last()
{
    if (_row < rowCount() - 1) {
        setTimestamp(data(index(rowCount() - 1, 0), MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch());

        if (_animated) {
            _timer->stop();
            _animated = false;
            emit animatedChanged();
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

    emit animatedChanged();
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
