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

#ifndef VREMENAR_WEATHERPROVIDERBASE_H_
#define VREMENAR_WEATHERPROVIDERBASE_H_

#include <QtCore/QTimer>

#include "common/api/APILoader.h"
#include "common/containers/Hyperlink.h"
#include "weather/common/Weather.h"
#include "weather/common/models/ForecastProxyModel.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/models/MapLegendProxyModel.h"

namespace Vremenar
{
class NetworkManager;

class WeatherProviderBase : public APILoader
{
    Q_OBJECT
public:
    explicit WeatherProviderBase(NetworkManager *network,
                                 const QVariant &defaultCoordinates,
                                 QObject *parent = nullptr);

    Q_PROPERTY(qreal minZoomLevel READ minZoomLevel CONSTANT)
    Q_PROPERTY(qreal maxZoomLevel READ maxZoomLevel CONSTANT)
    Q_PROPERTY(QVariant defaultMapCoordinates READ defaultMapCoordinates CONSTANT)
    Q_PROPERTY(QJsonObject copyrightLink READ copyrightLinkJson CONSTANT)
    Q_PROPERTY(QDateTime lastUpdateTime READ lastUpdateTime NOTIFY lastUpdateTimeChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)

    inline ForecastProxyModel *forecast() { return _forecastProxyModel.get(); }
    inline MapInfoModel *mapInfo() { return _mapInfoModel.get(); }
    inline MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel.get(); }
    inline MapLegendProxyModel *mapLegend() { return _mapLegendProxyModel.get(); }

    virtual void requestForecastDetails(int index) = 0;
    virtual void requestMapLayers(Weather::MapType type) = 0;

    [[nodiscard]] virtual const std::vector<Weather::MapType> &supportedMapTypes() const = 0;
    [[nodiscard]] virtual qreal minZoomLevel() const = 0;
    [[nodiscard]] virtual qreal maxZoomLevel() const = 0;
    [[nodiscard]] virtual QVariant defaultMapCoordinates() const = 0;
    [[nodiscard]] virtual Hyperlink *copyrightLink() const = 0;

    const QDateTime &lastUpdateTime() { return _lastUpdateResponseTime; }
    bool loading() { return _loading; }

public Q_SLOTS:
    Q_INVOKABLE void changeMapType(Weather::MapType type);
    Q_INVOKABLE void currentMapLayerChanged(int index);
    Q_INVOKABLE void refresh();

Q_SIGNALS:
    void lastUpdateTimeChanged();
    void loadingChanged();

protected:
    void startTimer();
    void setLastUpdatedTime(const QDateTime &time) { _lastUpdateResponseTime = time; }
    void setLoading(bool loading);

private:
    [[nodiscard]] inline QJsonObject copyrightLinkJson() const { return copyrightLink()->asJson(); }
    void timerCallback();

    std::unique_ptr<ForecastProxyModel> _forecastProxyModel;
    std::unique_ptr<MapInfoModel> _mapInfoModel;
    std::unique_ptr<MapLayersProxyModel> _mapLayersProxyModel;
    std::unique_ptr<MapLegendProxyModel> _mapLegendProxyModel;

    QDateTime _lastUpdateResponseTime{};
    bool _loading;

    Weather::MapType _currentType{Weather::UnknownMap};

    std::unique_ptr<QTimer> _timer{};
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDERBASE_H_
