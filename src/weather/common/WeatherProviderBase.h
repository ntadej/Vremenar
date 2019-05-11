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

#include "common/api/APILoader.h"
#include "common/containers/Hyperlink.h"
#include "weather/common/Weather.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"

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

    Q_PROPERTY(float minZoomLevel READ minZoomLevel CONSTANT)
    Q_PROPERTY(float maxZoomLevel READ maxZoomLevel CONSTANT)
    Q_PROPERTY(QVariant defaultMapCoordinates READ defaultMapCoordinates CONSTANT)
    Q_PROPERTY(QJsonObject copyrightLink READ copyrightLinkJson CONSTANT)

    inline MapInfoModel *mapInfo() { return _mapInfoModel.get(); }
    inline MapLayersProxyModel *mapLayers() { return _mapLayersProxyModel.get(); }

    Q_INVOKABLE void currentMapLayerChanged(int index);

    virtual void requestMapLayers(Weather::MapType type) = 0;

    virtual const std::vector<Weather::MapType> &supportedMapTypes() const = 0;
    virtual float minZoomLevel() const = 0;
    virtual float maxZoomLevel() const = 0;
    virtual QVariant defaultMapCoordinates() const = 0;
    virtual Hyperlink *copyrightLink() const = 0;

protected:
    std::unique_ptr<MapInfoModel> _mapInfoModel;
    std::unique_ptr<MapLayersProxyModel> _mapLayersProxyModel;

private:
    inline QJsonObject copyrightLinkJson() const { return copyrightLink()->asJson(); }
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERPROVIDERBASE_H_
