#
# Vremenar
# Copyright (C) 2021 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

SOURCES += \
    src/weather/CurrentWeather.cpp \
    src/weather/Sources.cpp \
    src/weather/Weather.cpp \
    src/weather/WeatherProvider.cpp \
    src/weather/api/APIMapLayers.cpp \
    src/weather/api/APIRequest.cpp \
    src/weather/api/APIStations.cpp \
    src/weather/containers/MapInfo.cpp \
    src/weather/containers/MapLayer.cpp \
    src/weather/containers/MapLegendItem.cpp \
    src/weather/containers/StationInfo.cpp \
    src/weather/containers/StationListItem.cpp \
    src/weather/containers/WeatherCondition.cpp \
    src/weather/containers/WeatherInfo.cpp \
    src/weather/models/MapInfoModel.cpp \
    src/weather/models/MapLayersModel.cpp \
    src/weather/models/MapLayersProxyModel.cpp \
    src/weather/models/MapLegendModel.cpp \
    src/weather/models/MapLegendProxyModel.cpp \
    src/weather/models/StationListModel.cpp \
    src/weather/models/WeatherMapModel.cpp \
    src/weather/models/WeatherMapProxyModel.cpp

HEADERS += \
    src/weather/CurrentWeather.h \
    src/weather/Sources.h \
    src/weather/Weather.h \
    src/weather/WeatherProvider.h \
    src/weather/api/APIMapLayers.h \
    src/weather/api/APIRequest.h \
    src/weather/api/APIStations.h \
    src/weather/containers/MapInfo.h \
    src/weather/containers/MapLayer.h \
    src/weather/containers/MapLegendItem.h \
    src/weather/containers/StationInfo.h \
    src/weather/containers/StationListItem.h \
    src/weather/containers/WeatherCondition.h \
    src/weather/containers/WeatherInfo.h \
    src/weather/models/MapInfoModel.h \
    src/weather/models/MapLayersModel.h \
    src/weather/models/MapLayersProxyModel.h \
    src/weather/models/MapLegendModel.h \
    src/weather/models/MapLegendProxyModel.h \
    src/weather/models/StationListModel.h \
    src/weather/models/WeatherMapModel.h \
    src/weather/models/WeatherMapProxyModel.h
