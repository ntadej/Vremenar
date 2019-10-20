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

#include <QtCore/QDebug>

#include "common/NetworkManager.h"
#include "weather/common/containers/MapInfo.h"

#include "weather/common/WeatherProviderBase.h"

namespace
{
constexpr uint32_t INTERVAL = 300000;
constexpr uint32_t PROTECTION = 60000;
} // namespace

namespace Vremenar
{

WeatherProviderBase::WeatherProviderBase(NetworkManager *network,
                                         const QVariant &defaultCoordinates,
                                         QObject *parent)
    : APILoader(network, parent),
      _mapInfoModel(std::make_unique<MapInfoModel>(this)),
      _mapLayersProxyModel(std::make_unique<MapLayersProxyModel>(defaultCoordinates, this)),
      _mapLegendProxyModel(std::make_unique<MapLegendProxyModel>(this)),
      _timer(std::make_unique<QTimer>(this))
{
    _timer->setSingleShot(true);

    connect(_timer.get(), &QTimer::timeout, this, &WeatherProviderBase::timerCallback);
}

void WeatherProviderBase::changeMapType(Weather::MapType type)
{
    if (_currentType == type) {
        return;
    }

    _currentType = type;
    _mapLegendProxyModel->setType(_currentType);
    refresh();
}

void WeatherProviderBase::currentMapLayerChanged(int index)
{
    changeMapType(_mapInfoModel->row<MapInfo>(index)->type());
}

void WeatherProviderBase::refresh()
{
    _timer->stop();

    _lastUpdateRequestTime = QDateTime::currentDateTime();
    requestMapLayers(_currentType);
}

void WeatherProviderBase::startTimer()
{
    _timer->start(INTERVAL);

    qDebug() << "Autorefresh:"
             << "Starting timer...";
}

void WeatherProviderBase::timerCallback()
{
    _timer->stop();

    auto now = QDateTime::currentDateTime();
    if (_lastUpdateResponseTime.msecsTo(now) < PROTECTION) {
        qDebug() << "Autorefresh:"
                 << "Already requested information less than" << PROTECTION << "ms ago.";
        startTimer();
        return;
    }

    qDebug() << "Autorefresh:"
             << "Reloading...";

    _lastUpdateRequestTime = now;
    requestMapLayers(_currentType);
}

} // namespace Vremenar
