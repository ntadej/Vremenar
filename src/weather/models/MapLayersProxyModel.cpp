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

#include <QtCore/QLocale>

#include "weather/containers/MapLayer.h"

#include "weather/models/MapLayersProxyModel.h"

namespace
{
constexpr int timerInterval{500};
constexpr int timerIntervalLong{750};

constexpr qint64 msecInDay{86400000};
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
        emitUpdate();
    }
}

void MapLayersProxyModel::emitUpdate()
{
    QString urlPrevious;
    QString urlCurrent = data(index(_row, 0), MapLayer::UrlRole).toUrl().toString();
    QString urlNext;
    if (urlCurrent.contains(QStringLiteral("json"))) {
        urlCurrent = QString();
    } else {
        if (_row > 0) {
            urlPrevious = data(index(_row - 1, 0), MapLayer::UrlRole).toUrl().toString();
        } else {
            urlPrevious = data(index(rowCount() - 1, 0), MapLayer::UrlRole).toUrl().toString();
        }
        if (_row + 1 < rowCount()) {
            urlNext = data(index(_row + 1, 0), MapLayer::UrlRole).toUrl().toString();
        } else {
            urlNext = data(index(0, 0), MapLayer::UrlRole).toUrl().toString();
        }
    }

    emit timestampChanged();
    emit mapChanged(_type, _renderingType, urlPrevious, urlCurrent, urlNext);
}

int MapLayersProxyModel::currentIndex() const
{
    if (rowCount() == 0) {
        return 0;
    }

    return _row;
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
        if (_daily) {
            return tr("today");
        }
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
    if (rowCount() == 0) {
        return tr("Vremenar");
    }

    auto type = data(index(0, 0), MapLayer::TypeRole).value<Weather::MapType>();
    return Weather::mapTypeToLocalizedString(type);
}

void MapLayersProxyModel::setCurrentIndex(int newIndex)
{
    if (newIndex != _row) {
        _row = newIndex;

        const QModelIndex in = index(_row, 0);
        _time = data(in, MapLayer::TimeRole).toDateTime().toMSecsSinceEpoch();
        _type = Weather::MapType(data(in, MapLayer::TypeRole).toInt());
        _renderingType = Weather::MapRenderingType(data(in, MapLayer::RenderingRole).toInt());
        _coordinates = data(in, MapLayer::CoordinatesRole);

        if (!_updating) {
            emitUpdate();
        }
    }
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
                _coordinates = data(in, MapLayer::CoordinatesRole);
                _row = i;
                break;
            }
        }

        if (!_updating) {
            emitUpdate();
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

    if (rowCount() > 0) {
        _daily = data(index(0, 0), MapLayer::TimeRole).toDateTime().msecsTo(data(index(1, 0), MapLayer::TimeRole).toDateTime()) == msecInDay;
    } else {
        _daily = false;
    }

    qint64 newDefault{};
    for (int i = 0; i < rowCount(); i++) {
        const QModelIndex in = index(i, 0);
        auto observation = data(in, MapLayer::ObservationRole).value<Weather::ObservationType>();
        if (observation == Weather::Recent || observation == Weather::Forecast) {
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
