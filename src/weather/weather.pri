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
    src/weather/common/containers/ForecastEntry.cpp \
    src/weather/common/containers/MapInfo.cpp \
    src/weather/common/containers/MapLayer.cpp \
    src/weather/common/containers/MapLegendItem.cpp \
    src/weather/common/models/ForecastModelBase.cpp \
    src/weather/common/models/ForecastProxyModel.cpp \
    src/weather/common/models/MapInfoModel.cpp \
    src/weather/common/models/MapLayersModelBase.cpp \
    src/weather/common/models/MapLayersProxyModel.cpp \
    src/weather/common/models/MapLegendModelBase.cpp \
    src/weather/common/models/MapLegendProxyModel.cpp \
    src/weather/arso/ARSOCommon.cpp \
    src/weather/arso/ARSOCurrentWeather.cpp \
    src/weather/arso/ARSOWeatherProvider.cpp \
    src/weather/arso/api/ARSOAPILocations.cpp \
    src/weather/arso/api/ARSOAPIMapLayers.cpp \
    src/weather/arso/api/ARSOAPIRequest.cpp \
    src/weather/arso/models/ARSOForecastModel.cpp \
    src/weather/arso/models/ARSOMapLayersModel.cpp \
    src/weather/arso/models/ARSOMapLegendModel.cpp \
    src/weather/backend/Common.cpp \
    src/weather/backend/CurrentWeather.cpp \
    src/weather/backend/WeatherProvider.cpp \
    src/weather/backend/api/APILocations.cpp \
    src/weather/backend/api/APIMapLayers.cpp \
    src/weather/backend/api/APIRequest.cpp \
    src/weather/backend/models/ForecastModel.cpp \
    src/weather/backend/models/MapLayersModel.cpp \
    src/weather/backend/models/MapLegendModel.cpp

HEADERS += \
    src/weather/common/CurrentWeatherBase.h \
    src/weather/common/Weather.h \
    src/weather/common/WeatherProviderBase.h \
    src/weather/common/containers/ForecastEntry.h \
    src/weather/common/containers/MapInfo.h \
    src/weather/common/containers/MapLayer.h \
    src/weather/common/containers/MapLegendItem.h \
    src/weather/common/models/ForecastModelBase.h \
    src/weather/common/models/ForecastProxyModel.h \
    src/weather/common/models/MapInfoModel.h \
    src/weather/common/models/MapLayersModelBase.h \
    src/weather/common/models/MapLayersProxyModel.h \
    src/weather/common/models/MapLegendModelBase.h \
    src/weather/common/models/MapLegendProxyModel.h \
    src/weather/arso/ARSOCommon.h \
    src/weather/arso/ARSOCurrentWeather.h \
    src/weather/arso/ARSOWeatherProvider.h \
    src/weather/arso/api/ARSOAPILocations.h \
    src/weather/arso/api/ARSOAPIMapLayers.h \
    src/weather/arso/api/ARSOAPIRequest.h \
    src/weather/arso/models/ARSOForecastModel.h \
    src/weather/arso/models/ARSOMapLayersModel.h \
    src/weather/arso/models/ARSOMapLegendModel.h \
    src/weather/backend/Common.h \
    src/weather/backend/CurrentWeather.h \
    src/weather/backend/WeatherProvider.h \
    src/weather/backend/api/APILocations.h \
    src/weather/backend/api/APIMapLayers.h \
    src/weather/backend/api/APIRequest.h \
    src/weather/backend/models/ForecastModel.h \
    src/weather/backend/models/MapLayersModel.h \
    src/weather/backend/models/MapLegendModel.h
