#
# Vremenar
# Copyright (C) 2024 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

cmake_minimum_required(VERSION 3.23)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(config/Version.cmake)

project(Vremenar VERSION ${VREMENAR_VERSION} LANGUAGES CXX)

# Define common platforms
if(ANDROID OR IOS)
    set(MOBILE ON)
else()
    set(MOBILE OFF)
endif()

find_package(Qt6 6.7 COMPONENTS Gui Location Positioning Qml Quick QuickControls2 Sql REQUIRED)
if(NOT MOBILE)
    find_package(Qt6 6.7 COMPONENTS Widgets REQUIRED)
endif()
find_package(Qt6 6.7 OPTIONAL_COMPONENTS LinguistTools)
qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES de sl)

qt_policy(SET QTP0002 NEW)

if(ANDROID AND DEFINED ENV{QMapLibre_Android_DIR})
    message(STATUS "Setting QMapLibre_DIR to $ENV{QMapLibre_Android_DIR}/${ANDROID_ABI}/lib/cmake/QMapLibre")
    set(QMapLibre_DIR "$ENV{QMapLibre_Android_DIR}/${ANDROID_ABI}/lib/cmake/QMapLibre")
endif()

find_package(QMapLibre COMPONENTS Location REQUIRED)

include(Config.cmake)
include(config/Build.cmake)

add_subdirectory(src)
add_subdirectory(resources)
