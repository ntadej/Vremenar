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

# Debug
set(VREMENAR_NAME "Vremenar")
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR IOS)
        set(VREMENAR_NAME "VremenarDevel")
    endif()
endif()

# Define common platforms
if(ANDROID OR IOS)
    set(MOBILE ON)
else()
    SET(MOBILE OFF)
endif()

if(NOT MOBILE)
    find_package(Qt6 6.3 COMPONENTS Widgets REQUIRED)
endif()

# Positioning
option(POSITIONING "Enable positioning" ON)
message(STATUS "Positioning: ${POSITIONING}")

# logging
option(LOGGING "Enable logging" ON)
if(LOGGING)
    set(LOGGING_ENABLED true)
else()
    set(LOGGING_ENABLED false)
endif()
message(STATUS "Logging: ${LOGGING}")

# Store
option(STORE "Enable store deployment" OFF)
message(STATUS "Store deployment: ${STORE}")

# compiler
set(CMAKE_CXX_STANDARD 17)
set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml")

add_library(
    Vremenar-compiler-options INTERFACE
)

target_compile_options(
    Vremenar-compiler-options
    INTERFACE
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wall>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wconversion>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wextra>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wshadow>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Werror>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wno-unknown-pragmas>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wno-gnu-zero-variadic-macro-arguments>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-pedantic>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>:/utf-8>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>:/WX>   # all warnings as errors
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>:/EHsc> # exceptions
)

target_compile_definitions(
    Vremenar-compiler-options
    INTERFACE
        QT_DEPRECATED_WARNINGS
        $<$<CONFIG:Debug>:QT_QML_DEBUG>
        $<$<BOOL:${MOBILE}>:VREMENAR_MOBILE>
        $<$<BOOL:${POSITIONING}>:VREMENAR_POSITIONING>
        $<$<BOOL:${STORE}>:VREMENAR_STORE>
)

# Config summary
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Building for platform: macOS")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/macOS.cmake)
elseif(ANDROID)
    message(STATUS "Building for platform: Android")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/Android.cmake)
else()
    message(FATAL_ERROR "Unknown platform")
endif()

