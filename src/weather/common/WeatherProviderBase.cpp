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

#include "common/NetworkManager.h"
#include "weather/common/containers/MapInfo.h"

#include "weather/common/WeatherProviderBase.h"

namespace Vremenar
{

WeatherProviderBase::WeatherProviderBase(NetworkManager *network,
                                         const QVariant &defaultCoordinates,
                                         QObject *parent)
    : APILoader(network, parent),
      _mapInfoModel(std::make_unique<MapInfoModel>(this)),
      _mapLayersProxyModel(std::make_unique<MapLayersProxyModel>(defaultCoordinates, this)) {}

void WeatherProviderBase::currentMapLayerChanged(int index)
{
    requestMapLayers(_mapInfoModel->row<MapInfo>(index)->type());
}

} // namespace Vremenar
