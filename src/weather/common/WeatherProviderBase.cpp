/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/NetworkManager.h"
#include "weather/common/models/MapLayersProxyModel.h"

#include "weather/common/WeatherProviderBase.h"

namespace Vremenar
{

WeatherProviderBase::WeatherProviderBase(NetworkManager *network,
                                         QObject *parent)
    : APILoader(network, parent),
      _mapLayersProxyModel(std::make_unique<MapLayersProxyModel>(this)) {}

WeatherProviderBase::~WeatherProviderBase() = default;

} // namespace Vremenar
