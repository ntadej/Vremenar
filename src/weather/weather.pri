#
# Vremenar
# Copyright (C) 2020 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

SOURCES += \
    src/weather/common/CurrentWeatherBase.cpp \
    src/weather/common/Weather.cpp \
    src/weather/common/WeatherProviderBase.cpp \
    src/weather/common/containers/MapInfo.cpp \
    src/weather/common/containers/MapLayer.cpp \
    src/weather/common/containers/MapLegendItem.cpp \
    src/weather/common/containers/WeatherInfo.cpp \
    src/weather/common/models/MapInfoModel.cpp \
    src/weather/common/models/MapLayersModelBase.cpp \
    src/weather/common/models/MapLayersProxyModel.cpp \
    src/weather/common/models/MapLegendModelBase.cpp \
    src/weather/common/models/MapLegendProxyModel.cpp \
    src/weather/common/models/WeatherMapModelBase.cpp \
    src/weather/common/models/WeatherMapProxyModel.cpp \
    src/weather/backend/Common.cpp \
    src/weather/backend/CurrentWeather.cpp \
    src/weather/backend/WeatherProvider.cpp \
    src/weather/backend/api/APILocations.cpp \
    src/weather/backend/api/APIMapLayers.cpp \
    src/weather/backend/api/APIRequest.cpp \
    src/weather/backend/models/MapLayersModel.cpp \
    src/weather/backend/models/MapLegendModel.cpp \
    src/weather/backend/models/WeatherMapModel.cpp

HEADERS += \
    src/weather/common/CurrentWeatherBase.h \
    src/weather/common/Weather.h \
    src/weather/common/WeatherProviderBase.h \
    src/weather/common/containers/MapInfo.h \
    src/weather/common/containers/MapLayer.h \
    src/weather/common/containers/MapLegendItem.h \
    src/weather/common/containers/WeatherInfo.h \
    src/weather/common/models/MapInfoModel.h \
    src/weather/common/models/MapLayersModelBase.h \
    src/weather/common/models/MapLayersProxyModel.h \
    src/weather/common/models/MapLegendModelBase.h \
    src/weather/common/models/MapLegendProxyModel.h \
    src/weather/common/models/WeatherMapModelBase.h \
    src/weather/common/models/WeatherMapProxyModel.h \
    src/weather/backend/Common.h \
    src/weather/backend/CurrentWeather.h \
    src/weather/backend/WeatherProvider.h \
    src/weather/backend/api/APILocations.h \
    src/weather/backend/api/APIMapLayers.h \
    src/weather/backend/api/APIRequest.h \
    src/weather/backend/models/MapLayersModel.h \
    src/weather/backend/models/MapLegendModel.h \
    src/weather/backend/models/WeatherMapModel.h
