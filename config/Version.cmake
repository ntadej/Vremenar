#
# Vremenar
# Copyright (C) 2023 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

# Vremenar version number
file(READ "${CMAKE_SOURCE_DIR}/config/VERSION" VREMENAR_VERSION)
string(REGEX REPLACE "\n" "" VREMENAR_VERSION "${VREMENAR_VERSION}") # get rid of the newline at the end

set(VREMENAR_BUILD "" CACHE STRING "Vremenar build number override")

# Find Git Version Patch
find_program(GIT git)
if(GIT)
    execute_process(
        COMMAND ${GIT} rev-list --count HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE VREMENAR_BUILD_NUMBER OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(VREMENAR_BUILD)
        set(VREMENAR_BUILD_NUMBER ${VREMENAR_BUILD})
    endif()
else()
    message(FATAL_ERROR "Git exectutable not found")
endif()

message(STATUS "Building Vremenar version ${VREMENAR_VERSION}")
message(STATUS "Build number: ${VREMENAR_BUILD_NUMBER}")
