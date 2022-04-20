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

# Vremenar version number
file(READ "${CMAKE_SOURCE_DIR}/config/VERSION" VREMENAR_VERSION)
string(REGEX REPLACE "\n" "" VREMENAR_VERSION "${VREMENAR_VERSION}") # get rid of the newline at the end

# Find Git Version Patch
FIND_PROGRAM(GIT git)
IF(GIT)
    EXECUTE_PROCESS(
        COMMAND ${GIT} rev-list --count HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE VREMENAR_BUILD OUTPUT_STRIP_TRAILING_WHITESPACE
    )
ELSE()
    message(FATAL_ERROR "Git exectutable not found")
ENDIF()

message(STATUS "Building Vremenar version ${VREMENAR_VERSION}")
message(STATUS "Build number: ${VREMENAR_BUILD}")
