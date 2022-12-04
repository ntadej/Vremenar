#
# Vremenar
# Copyright (C) 2022 Tadej Novak <tadej@tano.si>
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

find_package(Qt6 6.4 COMPONENTS Gui Location Positioning Qml Quick QuickControls2 Sql REQUIRED)
qt_standard_project_setup()

include(Config.cmake)
include(config/Build.cmake)

add_subdirectory(src)
add_subdirectory(resources)
