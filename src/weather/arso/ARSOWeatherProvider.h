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

#ifndef VREMENAR_ARSOWEATHERPROVIDER_H_
#define VREMENAR_ARSOWEATHERPROVIDER_H_

#include "weather/arso/models/ARSOMapLayersModel.h"
#include "weather/arso/models/ARSOMapLegendModel.h"
#include "weather/common/Weather.h"
#include "weather/common/WeatherProviderBase.h"

namespace Vremenar
{
namespace ARSO
{

class WeatherProvider : public WeatherProviderBase
{
    Q_OBJECT
public:
    explicit WeatherProvider(NetworkManager *network,
                             QObject *parent = nullptr);

    Q_INVOKABLE void requestMapLayers(Weather::MapType type) final;

    inline const std::vector<Weather::MapType> &supportedMapTypes() const final { return _supportedMapTypes; }
    inline float minZoomLevel() const final { return 7; }
    inline float maxZoomLevel() const final { return 10; }
    QVariant defaultMapCoordinates() const final;
    inline Hyperlink *copyrightLink() const final { return _copyrightLink.get(); }

protected Q_SLOTS:
    void response(QNetworkReply *reply) final;

private:
    const std::vector<Weather::MapType> _supportedMapTypes{
        Weather::PrecipitationMap,
        Weather::CloudCoverageMap,
        Weather::WindSpeedMap,
        Weather::TemperatureMap,
        Weather::HailProbabilityMap};

    std::unique_ptr<MapLayersModel> _mapLayersModel;
    std::unique_ptr<MapLegendModel> _mapLegendModel;

    std::unique_ptr<Hyperlink> _copyrightLink;
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOWEATHERPROVIDER_H_
