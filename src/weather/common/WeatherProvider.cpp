/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/NetworkManager.h"
#include "weather/common/WeatherProvider.h"
#include "weather/common/models/MapLayersProxyModel.h"

WeatherProvider::WeatherProvider(NetworkManager *network,
                                 QObject *parent)
    : APILoader(network, parent),
      _mapLayersProxyModel(new MapLayersProxyModel(this)) {}

WeatherProvider::~WeatherProvider() {}
