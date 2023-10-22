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
if (${CMAKE_OSX_SYSROOT} MATCHES "iphonesimulator")
    set(APPLE_IOS_VARIANT "iOSSimulator")
else()
    set(APPLE_IOS_VARIANT "iOS")
endif()

set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "iOS deployment target")

# Deployment target and rpath
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH
    "@executable_path/Frameworks"
    "/usr/lib/swift"
)

# Common paths
set(APPLE_XCODE_PATH "/Applications/Xcode.app")
set(APPLE_SWIFT_SDK_PATH "/usr/lib/swift")
set(APPLE_SWIFT_TOOLCHAIN_PATH "${APPLE_XCODE_PATH}/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/${CMAKE_OSX_SYSROOT}")

# Info.plist & deployment
configure_file("${CMAKE_SOURCE_DIR}/resources/iOS/Info.plist.in" "${CMAKE_BINARY_DIR}/Info.plist" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/resources/iOS/Vremenar.entitlements" "${CMAKE_BINARY_DIR}/Vremenar.entitlements" COPYONLY)
if(VREMENAR_STORE)
    configure_file("${CMAKE_SOURCE_DIR}/resources/iOS/AppStoreExport.plist" "${CMAKE_BINARY_DIR}/AppStoreExport.plist" COPYONLY)
endif()

# Assets
set(APPLE_IOS_ASSET_CATALOGS "${CMAKE_SOURCE_DIR}/resources/iOS/Assets.xcassets")
set(APPLE_IOS_STORYBOARD "${CMAKE_SOURCE_DIR}/resources/iOS/VremenarLaunchScreen.storyboard")

set(APPLE_IOS_TRANSLATIONS
    ${CMAKE_SOURCE_DIR}/resources/iOS/en.lproj
    ${CMAKE_SOURCE_DIR}/resources/iOS/de.lproj
    ${CMAKE_SOURCE_DIR}/resources/iOS/sl.lproj
)

# Dependencies
set(CARTHAGE_PATH "${CMAKE_SOURCE_DIR}/Carthage/Build")

find_library(Countly Countly HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
set(APPLE_IOS_EMBED_FRAMEWORKS ${Countly})

# Firebase
configure_file("${CMAKE_SOURCE_DIR}/GoogleService-Info.plist" "${CMAKE_BINARY_DIR}/GoogleService-Info.plist" COPYONLY)
set(APPLE_IOS_GOOGLESERVICE "${CMAKE_BINARY_DIR}/GoogleService-Info.plist")

find_library(nanopb nanopb HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(FBLPromises FBLPromises HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(GoogleDataTransport GoogleDataTransport HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(GoogleUtilities GoogleUtilities HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(FirebaseCore FirebaseCore HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(FirebaseCoreInternal FirebaseCoreInternal HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(FirebaseInstallations FirebaseInstallations HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
find_library(FirebaseMessaging FirebaseMessaging HINTS ${CARTHAGE_PATH} REQUIRED NO_CMAKE_FIND_ROOT_PATH)
