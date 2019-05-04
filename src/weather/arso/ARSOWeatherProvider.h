/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ARSOWEATHERPROVIDER_H_
#define VREMENAR_ARSOWEATHERPROVIDER_H_

#include "weather/common/Weather.h"
#include "weather/common/WeatherProviderBase.h"

namespace Vremenar
{
namespace ARSO
{
class MapLayersModel;

class WeatherProvider : public WeatherProviderBase
{
    Q_OBJECT
public:
    explicit WeatherProvider(NetworkManager *network,
                             QObject *parent = nullptr);
    virtual ~WeatherProvider() final;

    Q_INVOKABLE virtual void requestMapLayers(Weather::MapType type) final;

    inline virtual const std::vector<Weather::MapType> &supportedMapTypes() const final { return _supportedMapTypes; }
    inline virtual float minZoomLevel() const final { return 7; }
    inline virtual float maxZoomLevel() const final { return 10; }
    virtual QVariant defaultMapCoordinates() const final;

protected slots:
    virtual void response(QNetworkReply *reply) final;

private:
    const std::vector<Weather::MapType> _supportedMapTypes{
        Weather::PrecipitationMap,
        Weather::CloudCoverageMap,
        Weather::WindSpeedMap,
        Weather::TemperatureMap,
        Weather::HailProbabilityMap};

    std::unique_ptr<MapLayersModel> _mapLayersModel;
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOWEATHERPROVIDER_H_
