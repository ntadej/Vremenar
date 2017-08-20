/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_WEATHERPROVIDER_H_
#define VREMENAR_WEATHERPROVIDER_H_

#include "weather/common/Weather.h"
#include "weather/common/api/APILoader.h"

class NetworkManager;
class MapLayersProxyModel;

class WeatherProvider : public APILoader
{
    Q_OBJECT
public:
    explicit WeatherProvider(NetworkManager *network = nullptr,
                             QObject *parent = nullptr);
    virtual ~WeatherProvider();

    inline MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel; }

    virtual void requestMapLayers(Vremenar::Weather::MapType type) = 0;

protected:
    MapLayersProxyModel *_mapLayersProxyModel;
};

#endif // VREMENAR_WEATHERPROVIDER_H_
