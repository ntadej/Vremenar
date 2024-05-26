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

# Common resources
add_subdirectory(Common)
add_subdirectory(Common/ui)
add_subdirectory(Weather/Map)

# Desktop common resources
if(NOT MOBILE)
    add_subdirectory(Common/icons)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_subdirectory(macOS)
    add_subdirectory(Weather/TrayMask)
else()
    add_subdirectory(Linux)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")  # TODO: Windows
    add_subdirectory(Weather/Tray)
endif()
