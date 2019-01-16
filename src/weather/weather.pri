#
# Vremenar
# Copyright (C) 2019 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

SOURCES += \
    src/weather/common/Weather.cpp \
    src/weather/common/WeatherProviderBase.cpp \
    src/weather/common/containers/MapInfo.cpp \
    src/weather/common/containers/MapLayer.cpp \
    src/weather/common/models/MapInfoModel.cpp \
    src/weather/common/models/MapLayersModelBase.cpp \
    src/weather/common/models/MapLayersProxyModel.cpp \
    src/weather/arso/ARSOWeatherProvider.cpp \
    src/weather/arso/api/ARSOAPICommon.cpp \
    src/weather/arso/api/ARSOAPIMapLayers.cpp \
    src/weather/arso/api/ARSOAPIRequest.cpp \
    src/weather/arso/models/ARSOMapLayersModel.cpp

HEADERS += \
    src/weather/common/Weather.h \
    src/weather/common/WeatherProviderBase.h \
    src/weather/common/containers/MapInfo.h \
    src/weather/common/containers/MapLayer.h \
    src/weather/common/models/MapInfoModel.h \
    src/weather/common/models/MapLayersModelBase.h \
    src/weather/common/models/MapLayersProxyModel.h \
    src/weather/arso/ARSOWeatherProvider.h \
    src/weather/arso/api/ARSOAPICommon.h \
    src/weather/arso/api/ARSOAPIMapLayers.h \
    src/weather/arso/api/ARSOAPIRequest.h \
    src/weather/arso/models/ARSOMapLayersModel.h
