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

#ifndef VREMENAR_WEATHERPROVIDER_H_
#define VREMENAR_WEATHERPROVIDER_H_

#include "application/analytics/Analytics.h"
#include "common/api/APILoader.h"
#include "weather/Weather.h"

#include <QtCore/QDateTime>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>
#include <QtPositioning/QGeoCoordinate>

#include <memory>

class QTimer;

namespace Vremenar
{

class CurrentWeather;
class MapInfoModel;
class MapLayersModel;
class MapLayersProxyModel;
class MapLegendModel;
class MapLegendProxyModel;
class NetworkManager;
class StationListModel;
class WeatherMapModel;
class WeatherMapProxyModel;

class WeatherProvider : public APILoader
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(WeatherProvider)
public:
    explicit WeatherProvider(NetworkManager *network,
                             QObject *parent = nullptr);
    ~WeatherProvider() override;

    Q_PROPERTY(qreal minZoomLevel READ minZoomLevel NOTIFY sourceChanged)
    Q_PROPERTY(qreal maxZoomLevel READ maxZoomLevel NOTIFY sourceChanged)
    Q_PROPERTY(QDateTime lastUpdateTime READ lastUpdateTime NOTIFY lastUpdateTimeChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(int currentMapStyle READ currentMapStyle WRITE currentMapStyleChanged NOTIFY currentMapStyleChangedSignal)
    Q_PROPERTY(int currentMapLayer READ currentMapLayer WRITE currentMapLayerChanged NOTIFY currentMapLayerChangedSignal)
    Q_PROPERTY(int currentSource READ currentSource NOTIFY sourceChanged)
    Q_PROPERTY(int currentType READ currentType NOTIFY currentMapLayerChangedSignal)
    Q_PROPERTY(bool currentMapLayerHasLegend READ currentMapLayerHasLegend NOTIFY currentMapLayerHasLegendChangedSignal)

    CurrentWeather *current() { return _currentWeather.get(); }
    WeatherMapProxyModel *weatherMap() { return _weatherMapProxyModel.get(); }
    MapInfoModel *mapInfo() { return _mapInfoModel.get(); }
    MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel.get(); }
    MapLegendProxyModel *mapLegend() { return _mapLegendProxyModel.get(); }
    StationListModel *stations() { return _stationsModel.get(); }
    StationListModel *stationsWithCurrentCondition() { return _stationsWithCurrentConditionModel.get(); }

    Q_INVOKABLE void requestStations();
    Q_INVOKABLE void requestBaseInfo();
    Q_INVOKABLE void requestCurrentWeatherInfo(const QGeoCoordinate &coordinate);
    Q_INVOKABLE void requestWeatherMapDetails(const QString &url);
    Q_INVOKABLE void requestMapLayers(Weather::MapType type);
    Q_INVOKABLE void resetSource(bool load = true);

    [[nodiscard]] bool currentMapLayerHasLegend() const;
    [[nodiscard]] qreal minZoomLevel() const;
    [[nodiscard]] qreal maxZoomLevel() const;

    [[nodiscard]] Weather::MapStyle currentStyle() const { return _currentStyle; }
    [[nodiscard]] Weather::MapType currentType() const { return _currentType; }
    [[nodiscard]] Weather::Source currentSource() const { return _currentSource; }
    [[nodiscard]] int currentMapStyle() const;
    [[nodiscard]] int currentMapLayer() const;
    [[nodiscard]] const QDateTime &lastUpdateTime() const { return _lastUpdateResponseTime; }
    [[nodiscard]] bool loading() const { return _loading; }

public slots:
    Q_INVOKABLE void changeMapStyle(Weather::MapStyle style,
                                    bool action = false);
    Q_INVOKABLE void changeMapType(Weather::MapType type,
                                   bool action = false);
    Q_INVOKABLE void currentLocationStatusChanged(bool enabled);
    Q_INVOKABLE void currentMapStyleChanged(int index);
    Q_INVOKABLE void currentMapLayerChanged(int index);
    Q_INVOKABLE void refresh();

signals:
    void recordEvent(Analytics::EventType, const QString &); // NOLINT(readability-named-parameter)
    void lastUpdateTimeChanged();
    void lastUpdateTimeChangedCurrent();
    void loadingChanged();
    void loadingSuccess();
    void loadingError();
    void currentMapStyleChangedSignal(int);           // NOLINT(readability-named-parameter)
    void currentMapLayerChangedSignal(int);           // NOLINT(readability-named-parameter)
    void currentMapLayerHasLegendChangedSignal(bool); // NOLINT(readability-named-parameter)
    void stationsUpdated();
    void storeState();
    void sourceChanged();

private slots:
    void response(QNetworkReply *reply) final;
    void error(QNetworkReply *reply,
               QNetworkReply::NetworkError err) final;
    void currentTimeChanged();

private:
    void startTimer();
    void startTimerCurrent();
    void stopTimerCurrent();
    void setLoading(bool loading);

    void timerCallback();
    void timerCallbackCurrent();

    std::unique_ptr<CurrentWeather> _currentWeather;
    std::unique_ptr<WeatherMapModel> _weatherMapModelBase;
    std::unique_ptr<WeatherMapModel> _weatherMapModel;
    std::unique_ptr<WeatherMapProxyModel> _weatherMapProxyModel;
    std::unique_ptr<MapInfoModel> _mapInfoModel;
    std::unique_ptr<MapLayersModel> _mapLayersModel;
    std::unique_ptr<MapLayersProxyModel> _mapLayersProxyModel;
    std::unique_ptr<MapLegendModel> _mapLegendModel;
    std::unique_ptr<MapLegendProxyModel> _mapLegendProxyModel;
    std::unique_ptr<StationListModel> _stationsModel;
    std::unique_ptr<StationListModel> _stationsWithCurrentConditionModel;

    QDateTime _lastUpdateResponseTime;
    QDateTime _lastUpdateResponseTimeCurrent;
    bool _loading{false};

    Weather::MapStyle _currentStyle{Weather::UnknownMapStyle};
    Weather::MapType _currentType{Weather::UnknownMapType};
    Weather::Source _currentSource{Weather::Global};

    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<QTimer> _timerCurrent;
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDERBASE_H_
