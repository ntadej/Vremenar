/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_WEATHERPROVIDERBASE_H_
#define VREMENAR_WEATHERPROVIDERBASE_H_

#include "common/api/APILoader.h"
#include "weather/common/Weather.h"

namespace Vremenar
{
class MapLayersProxyModel;
class NetworkManager;

class WeatherProviderBase : public APILoader
{
    Q_OBJECT
public:
    explicit WeatherProviderBase(NetworkManager *network,
                                 QObject *parent = nullptr);
    virtual ~WeatherProviderBase();

    inline MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel.get(); }

    virtual void requestMapLayers(Weather::MapType type) = 0;

protected:
    std::unique_ptr<MapLayersProxyModel> _mapLayersProxyModel;
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDERBASE_H_