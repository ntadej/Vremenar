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

#ifndef VREMENAR_WEATHERPROVIDERBASE_H_
#define VREMENAR_WEATHERPROVIDERBASE_H_

#include <QtCore/QTimer>
#include <QtPositioning/QGeoCoordinate>

#include "application/analytics/Analytics.h"
#include "common/api/APILoader.h"
#include "common/containers/Hyperlink.h"
#include "weather/common/CurrentWeatherBase.h"
#include "weather/common/Weather.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/models/MapLegendProxyModel.h"
#include "weather/common/models/WeatherMapProxyModel.h"

namespace Vremenar
{
class NetworkManager;

class WeatherProviderBase : public APILoader
{
    Q_OBJECT
public:
    explicit WeatherProviderBase(NetworkManager *network,
                                 QObject *parent = nullptr);

    Q_PROPERTY(qreal minZoomLevel READ minZoomLevel CONSTANT)
    Q_PROPERTY(qreal maxZoomLevel READ maxZoomLevel CONSTANT)
    Q_PROPERTY(QJsonObject copyrightLink READ copyrightLinkJson CONSTANT)
    Q_PROPERTY(QDateTime lastUpdateTime READ lastUpdateTime NOTIFY lastUpdateTimeChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(int currentMapLayer READ currentMapLayer WRITE currentMapLayerChanged NOTIFY currentMapLayerChangedSignal)
    Q_PROPERTY(int currentMapLayerHasLegend READ currentMapLayerHasLegend NOTIFY currentMapLayerChangedSignal)

    inline CurrentWeatherBase *current() { return _currentWeather.get(); }
    inline WeatherMapProxyModel *weatherMap() { return _weatherMapProxyModel.get(); }
    inline MapInfoModel *mapInfo() { return _mapInfoModel.get(); }
    inline MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel.get(); }
    inline MapLegendProxyModel *mapLegend() { return _mapLegendProxyModel.get(); }

    virtual void requestCurrentWeatherInfo(const QGeoCoordinate &coordinate) = 0;
    virtual void requestWeatherMapDetails(const QString &url) = 0;
    virtual void requestImage(const QString &url) = 0;
    virtual void requestMapLayers(Weather::MapType type) = 0;

    [[nodiscard]] virtual bool currentMapLayerHasLegend() const = 0;
    [[nodiscard]] virtual const std::vector<Weather::MapType> &supportedMapTypes() const = 0;
    [[nodiscard]] virtual qreal minZoomLevel() const = 0;
    [[nodiscard]] virtual qreal maxZoomLevel() const = 0;
    [[nodiscard]] virtual Hyperlink *copyrightLink() const = 0;

    [[nodiscard]] inline Weather::MapType currentType() const { return _currentType; }
    [[nodiscard]] inline const QDateTime &lastUpdateTime() const { return _lastUpdateResponseTime; }
    [[nodiscard]] inline bool loading() const { return _loading; }
    [[nodiscard]] int currentMapLayer() const;

public Q_SLOTS:
    Q_INVOKABLE void changeMapType(Weather::MapType type,
                                   bool action = false);
    Q_INVOKABLE void currentMapLayerChanged(int index);
    Q_INVOKABLE void refresh();

Q_SIGNALS:
    void recordEvent(Analytics::EventType, const QString &payload);
    void lastUpdateTimeChanged();
    void lastUpdateTimeChangedCurrent();
    void loadingChanged();
    void currentMapLayerChangedSignal(int);
    void storeState();

protected:
    void setupCurrentWeather(std::unique_ptr<CurrentWeatherBase> ptr) { _currentWeather = std::move(ptr); }
    void startTimer();
    void startTimerCurrent();
    void stopTimerCurrent();
    void setLastUpdatedTime(const QDateTime &time) { _lastUpdateResponseTime = time; }
    void setLastUpdatedTimeCurrent(const QDateTime &time) { _lastUpdateResponseTimeCurrent = time; }
    void setLoading(bool loading);

private:
    [[nodiscard]] inline QJsonObject copyrightLinkJson() const { return copyrightLink()->asJson(); }
    void timerCallback();
    void timerCallbackCurrent();

    std::unique_ptr<CurrentWeatherBase> _currentWeather{};
    std::unique_ptr<WeatherMapProxyModel> _weatherMapProxyModel{};
    std::unique_ptr<MapInfoModel> _mapInfoModel{};
    std::unique_ptr<MapLayersProxyModel> _mapLayersProxyModel{};
    std::unique_ptr<MapLegendProxyModel> _mapLegendProxyModel{};

    QDateTime _lastUpdateResponseTime{};
    QDateTime _lastUpdateResponseTimeCurrent{};
    bool _loading{false};

    Weather::MapType _currentType{Weather::UnknownMap};

    std::unique_ptr<QTimer> _timer{};
    std::unique_ptr<QTimer> _timerCurrent{};
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDERBASE_H_
