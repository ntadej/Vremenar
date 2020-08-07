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

#ifndef VREMENAR_WEATHERPROVIDER_H_
#define VREMENAR_WEATHERPROVIDER_H_

#include "weather/backend/Common.h"
#include "weather/backend/models/ForecastModel.h"
#include "weather/backend/models/MapLayersModel.h"
#include "weather/backend/models/MapLegendModel.h"
#include "weather/common/Weather.h"
#include "weather/common/WeatherProviderBase.h"

namespace Vremenar
{
namespace Backend
{

class WeatherProvider : public WeatherProviderBase
{
    Q_OBJECT
public:
    explicit WeatherProvider(NetworkManager *network,
                             QObject *parent = nullptr);

    Q_INVOKABLE void requestCurrentWeatherInfo(const QGeoCoordinate &coordinate) final;
    Q_INVOKABLE void requestImage(const QString &url) final;
    Q_INVOKABLE void requestForecastDetails(const QString &url) final;
    Q_INVOKABLE void requestMapLayers(Weather::MapType type) final;

    [[nodiscard]] bool currentMapLayerHasLegend() const final;
    [[nodiscard]] inline const std::vector<Weather::MapType> &supportedMapTypes() const final { return _supportedMapTypes; }
    [[nodiscard]] inline qreal minZoomLevel() const final { return Backend::minZoomLevel; }
    [[nodiscard]] inline qreal maxZoomLevel() const final { return Backend::maxZoomLevel; }
    [[nodiscard]] inline Hyperlink *copyrightLink() const final { return _copyrightLink.get(); }

private Q_SLOTS:
    void response(QNetworkReply *reply) final;
    void currentTimeChanged();

private:
    const std::vector<Weather::MapType> _supportedMapTypes{
        Weather::ForecastMap,
        Weather::PrecipitationMap,
        Weather::CloudCoverageMap,
        Weather::WindSpeedMap,
        Weather::TemperatureMap,
        Weather::HailProbabilityMap};

    std::unique_ptr<ForecastModel> _forecastModelBase;
    std::unique_ptr<ForecastModel> _forecastModel;
    std::unique_ptr<MapLayersModel> _mapLayersModel;
    std::unique_ptr<MapLegendModel> _mapLegendModel;

    std::unique_ptr<Hyperlink> _copyrightLink;
};

} // namespace Backend
} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDER_H_
