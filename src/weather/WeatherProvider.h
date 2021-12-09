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

#ifndef VREMENAR_WEATHERPROVIDER_H_
#define VREMENAR_WEATHERPROVIDER_H_

#include <QtCore/QTimer>
#include <QtPositioning/QGeoCoordinate>

#include "application/analytics/Analytics.h"
#include "common/api/APILoader.h"
#include "common/containers/Hyperlink.h"
#include "weather/CurrentWeather.h"
#include "weather/Weather.h"
#include "weather/models/MapInfoModel.h"
#include "weather/models/MapLayersModel.h"
#include "weather/models/MapLayersProxyModel.h"
#include "weather/models/MapLegendModel.h"
#include "weather/models/MapLegendProxyModel.h"
#include "weather/models/StationListModel.h"
#include "weather/models/WeatherMapModel.h"
#include "weather/models/WeatherMapProxyModel.h"

namespace Vremenar
{
class NetworkManager;

class WeatherProvider : public APILoader
{
    Q_OBJECT
public:
    explicit WeatherProvider(NetworkManager *network,
                             QObject *parent = nullptr);

    Q_PROPERTY(qreal minZoomLevel READ minZoomLevel CONSTANT)
    Q_PROPERTY(qreal maxZoomLevel READ maxZoomLevel CONSTANT)
    Q_PROPERTY(QJsonObject copyrightLink READ copyrightLinkJson CONSTANT)
    Q_PROPERTY(QDateTime lastUpdateTime READ lastUpdateTime NOTIFY lastUpdateTimeChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(int currentMapStyle READ currentMapStyle WRITE currentMapStyleChanged NOTIFY currentMapStyleChangedSignal)
    Q_PROPERTY(int currentMapLayer READ currentMapLayer WRITE currentMapLayerChanged NOTIFY currentMapLayerChangedSignal)
    Q_PROPERTY(bool currentMapLayerHasLegend READ currentMapLayerHasLegend NOTIFY currentMapLayerHasLegendChangedSignal)

    inline CurrentWeather *current() { return _currentWeather.get(); }
    inline WeatherMapProxyModel *weatherMap() { return _weatherMapProxyModel.get(); }
    inline MapInfoModel *mapInfo() { return _mapInfoModel.get(); }
    inline MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel.get(); }
    inline MapLegendProxyModel *mapLegend() { return _mapLegendProxyModel.get(); }
    inline StationListModel *stations() { return _stationsModel.get(); }
    inline StationListModel *stationsWithCurrentCondition() { return _stationsWithCurrentConditionModel.get(); }

    Q_INVOKABLE void requestBaseInfo();
    Q_INVOKABLE void requestCurrentWeatherInfo(const QGeoCoordinate &coordinate);
    Q_INVOKABLE void requestWeatherMapDetails(const QString &url);
    Q_INVOKABLE void requestImage(const QString &url);
    Q_INVOKABLE void requestMapLayers(Weather::MapType type);

    [[nodiscard]] bool currentMapLayerHasLegend() const;
    [[nodiscard]] inline qreal minZoomLevel() const { return 7.5; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    [[nodiscard]] inline qreal maxZoomLevel() const { return 11; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    [[nodiscard]] inline Hyperlink *copyrightLink() const { return _copyrightLink.get(); }
    [[nodiscard]] inline QJsonObject copyrightLinkJson() const { return _copyrightLink->asJson(); }

    [[nodiscard]] inline Weather::MapStyle currentStyle() const { return _currentStyle; }
    [[nodiscard]] inline Weather::MapType currentType() const { return _currentType; }
    [[nodiscard]] int currentMapStyle() const;
    [[nodiscard]] int currentMapLayer() const;
    [[nodiscard]] inline const QDateTime &lastUpdateTime() const { return _lastUpdateResponseTime; }
    [[nodiscard]] inline bool loading() const { return _loading; }

public Q_SLOTS:
    Q_INVOKABLE void changeMapStyle(Weather::MapStyle style,
                                    bool action = false);
    Q_INVOKABLE void changeMapType(Weather::MapType type,
                                   bool action = false);
    Q_INVOKABLE void currentLocationStatusChanged(bool enabled);
    Q_INVOKABLE void currentMapStyleChanged(int index);
    Q_INVOKABLE void currentMapLayerChanged(int index);
    Q_INVOKABLE void refresh();

Q_SIGNALS:
    void recordEvent(Analytics::EventType, const QString &payload);
    void lastUpdateTimeChanged();
    void lastUpdateTimeChangedCurrent();
    void loadingChanged();
    void loadingSuccess();
    void loadingError();
    void currentMapStyleChangedSignal(int);
    void currentMapLayerChangedSignal(int);
    void currentMapLayerHasLegendChangedSignal(bool);
    void stationsUpdated();
    void storeState();

private Q_SLOTS:
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

    std::unique_ptr<CurrentWeather> _currentWeather{};
    std::unique_ptr<WeatherMapModel> _weatherMapModelBase{};
    std::unique_ptr<WeatherMapModel> _weatherMapModel{};
    std::unique_ptr<WeatherMapProxyModel> _weatherMapProxyModel{};
    std::unique_ptr<MapInfoModel> _mapInfoModel{};
    std::unique_ptr<MapLayersModel> _mapLayersModel{};
    std::unique_ptr<MapLayersProxyModel> _mapLayersProxyModel{};
    std::unique_ptr<MapLegendModel> _mapLegendModel{};
    std::unique_ptr<MapLegendProxyModel> _mapLegendProxyModel{};
    std::unique_ptr<StationListModel> _stationsModel{};
    std::unique_ptr<StationListModel> _stationsWithCurrentConditionModel{};

    std::unique_ptr<Hyperlink> _copyrightLink{};

    QDateTime _lastUpdateResponseTime{};
    QDateTime _lastUpdateResponseTimeCurrent{};
    bool _loading{false};

    Weather::MapStyle _currentStyle{Weather::UnknownMapStyle};
    Weather::MapType _currentType{Weather::UnknownMapType};

    std::unique_ptr<QTimer> _timer{};
    std::unique_ptr<QTimer> _timerCurrent{};
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDERBASE_H_
