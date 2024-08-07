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

# Debug
set(VREMENAR_NAME "Vremenar")
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR IOS)
        set(VREMENAR_NAME "VremenarDevel")
    endif()
endif()

# Positioning
option(VREMENAR_POSITIONING "Enable positioning" ON)
message(STATUS "Positioning: ${VREMENAR_POSITIONING}")

# logging
option(VREMENAR_LOGGING "Enable logging" ON)
if(VREMENAR_LOGGING)
    set(LOGGING_ENABLED true)
else()
    set(LOGGING_ENABLED false)
endif()
message(STATUS "Logging: ${VREMENAR_LOGGING}")

# Special builds for store
option(VREMENAR_STORE "Enable store deployment" OFF)
message(STATUS "Store deployment: ${VREMENAR_STORE}")

# compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOGEN_USE_SYSTEM_INCLUDE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(CMAKE_IS_XCODE 1)
else()
    set(CMAKE_IS_XCODE 0)
endif()
set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml")

# clang-tidy
set(CLANG_TIDY OFF CACHE BOOL "Enable clang tidy")
if (CLANG_TIDY)
    find_program(
        CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable"
    )
endif()
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy disabled or not found")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--header-filter=src/.*\.h")
endif()

# compiler options
add_library(
    Vremenar-compiler-options INTERFACE
)

target_compile_options(
    Vremenar-compiler-options
    INTERFACE
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wall>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wconversion>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wextra>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>,$<NOT:$<PLATFORM_ID:Linux>>>:-Wshadow>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>,$<NOT:$<BOOL:${CMAKE_IS_XCODE}>>>:-Werror>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>>:-Wno-unknown-pragmas>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<NOT:$<PLATFORM_ID:Windows>>,$<NOT:$<PLATFORM_ID:Linux>>>:-Wno-gnu-zero-variadic-macro-arguments>
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
        $<$<BOOL:${VREMENAR_POSITIONING}>:VREMENAR_POSITIONING>
        $<$<BOOL:${VREMENAR_STORE}>:VREMENAR_STORE>
)

# Config summary
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Building for platform: macOS")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/macOS.cmake)
elseif(IOS)
    message(STATUS "Building for platform: iOS")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/iOS.cmake)
elseif(ANDROID)
    message(STATUS "Building for platform: Android (${ANDROID_ABI})")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/Android.cmake)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Building for platform: Linux")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/Linux.cmake)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Building for platform: Windows")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/Windows.cmake)
else()
    message(FATAL_ERROR "Unknown platform")
endif()
