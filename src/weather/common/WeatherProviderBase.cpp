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
                                         QObject *parent)
    : APILoader(network, parent),
      _forecastProxyModel(std::make_unique<ForecastProxyModel>(this)),
      _mapInfoModel(std::make_unique<MapInfoModel>(this)),
      _mapLayersProxyModel(std::make_unique<MapLayersProxyModel>(this)),
      _mapLegendProxyModel(std::make_unique<MapLegendProxyModel>(this)),
      _timer(std::make_unique<QTimer>(this)),
      _timerCurrent(std::make_unique<QTimer>(this))
{
    _timer->setSingleShot(true);
    _timerCurrent->setSingleShot(true);

    connect(_timer.get(), &QTimer::timeout, this, &WeatherProviderBase::timerCallback);
    connect(_timerCurrent.get(), &QTimer::timeout, this, &WeatherProviderBase::timerCallbackCurrent);
}

void WeatherProviderBase::changeMapType(Weather::MapType type,
                                        bool action)
{
    if (_currentType == type) {
        return;
    }

    if (action) {
        Q_EMIT recordEvent(Analytics::MapTypeChanged, Weather::mapTypeString(type));
    }

    _currentType = type;
    _mapLegendProxyModel->setType(_currentType);

    Q_EMIT currentMapLayerChangedSignal(currentMapLayer());

    _timer->stop();
    requestMapLayers(_currentType);

    Q_EMIT storeState();
}

void WeatherProviderBase::currentMapLayerChanged(int index)
{
    if (index < 0 || index >= static_cast<int>(supportedMapTypes().size())) {
        return;
    }

    changeMapType(_mapInfoModel->row<MapInfo>(index)->type(), true);
}

int WeatherProviderBase::currentMapLayer() const
{
    const std::vector<Weather::MapType> &types = supportedMapTypes();
    auto it = std::find(types.begin(), types.end(), _currentType);
    return static_cast<int>(std::distance(types.begin(), it));
}

void WeatherProviderBase::refresh()
{
    _timer->stop();
    _timerCurrent->stop();

    requestMapLayers(_currentType);
    requestCurrentWeatherInfo(QGeoCoordinate());

    Q_EMIT storeState();
}

void WeatherProviderBase::startTimer()
{
    _timer->start(INTERVAL);

    qDebug() << "Autorefresh:"
             << "Starting timer...";
}

void WeatherProviderBase::startTimerCurrent()
{
    _timerCurrent->start(INTERVAL);

    qDebug() << "Autorefresh:"
             << "Starting current weather timer...";
}

void WeatherProviderBase::stopTimerCurrent()
{
    _timerCurrent->stop();
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

    setLastUpdatedTime(now);
    requestMapLayers(_currentType);

    Q_EMIT storeState();
}

void WeatherProviderBase::timerCallbackCurrent()
{
    _timerCurrent->stop();

    auto now = QDateTime::currentDateTime();
    if (_lastUpdateResponseTimeCurrent.msecsTo(now) < PROTECTION) {
        qDebug() << "Autorefresh:"
                 << "Already requested current weather information less than" << PROTECTION << "ms ago.";
        startTimer();
        return;
    }

    qDebug() << "Autorefresh:"
             << "Reloading current weather...";

    setLastUpdatedTimeCurrent(now);
    requestCurrentWeatherInfo(QGeoCoordinate());
}

void WeatherProviderBase::setLoading(bool loading)
{
    if (_loading != loading) {
        _loading = loading;
        Q_EMIT loadingChanged();
    }
}

} // namespace Vremenar
