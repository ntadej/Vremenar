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

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14")

set(BUNDLE_CONTENTS_PATH "${CMAKE_BINARY_DIR}/${VREMENAR_NAME}.app/Contents")
set(FRAMEWORKS_OUTPUT_PATH "${BUNDLE_CONTENTS_PATH}/Frameworks")
set(RESOURCES_OUTPUT_PATH "${BUNDLE_CONTENTS_PATH}/Resources")

# Deployment target and rpath
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH
    "@executable_path/../Frameworks"
    "/usr/lib/swift"
)

# Platform specific settings
set(APPLE_CODE_SIGN_IDENTITY "" CACHE STRING "macOS code signing identity")
set(APPLE_PKG_SIGN_IDENTITY "" CACHE STRING "macOS PKG signing identity")
set(APPLE_DEVELOPER_TEAM "" CACHE STRING "macOS Developer Team")

set(APPLE_XCODE_PATH "/Applications/Xcode.app" CACHE STRING "Xcode path")
set(APPLE_XCODE_VERSION_CODE "" CACHE STRING "Xcode version code")
set(APPLE_XCODE_BUILD "" CACHE STRING "Xcode build")
set(APPLE_SDK_VERSION "" CACHE STRING "macOS SDK version")
set(APPLE_SDK_BUILD "" CACHE STRING "macOS SDK build")
set(APPLE_SDK_PLATFORM_VERSION "" CACHE STRING "macOS SDK platform version")
set(APPLE_BUILD_MACHINE_OS_BUILD "" CACHE STRING "macOS build machine OS build")
set(APPLE_SWIFT_SDK_PATH "${CMAKE_OSX_SYSROOT}/usr/lib/swift")
set(APPLE_SWIFT_TOOLCHAIN_PATH "${APPLE_XCODE_PATH}/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/macosx")

if(VREMENAR_STORE)
    set(APPLE_ENTITLEMENTS_EXTRA_CONTENT "<key>com.apple.application-identifier</key>
    <string>${APPLE_DEVELOPER_TEAM}.si.tano.Vremenar</string>
    <key>com.apple.developer.team-identifier</key>
    <string>${APPLE_DEVELOPER_TEAM}</string>")
else()
    set(APPLE_ENTITLEMENTS_EXTRA_CONTENT "<key>com.apple.security.temporary-exception.mach-lookup.global-name</key>
    <array>
      <string>si.tano.Vremenar-spks</string>
      <string>si.tano.Vremenar-spki</string>
    </array>")
endif()

# Helper scripts
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/build_dmg.sh.in" "${CMAKE_BINARY_DIR}/build_dmg.sh" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/resign.sh.in" "${CMAKE_BINARY_DIR}/resign.sh" @ONLY)

# Info.plist & deployment
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/Info.plist.in" "${CMAKE_BINARY_DIR}/Info.plist" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/Vremenar.entitlements.in" "${CMAKE_BINARY_DIR}/Vremenar.entitlements" @ONLY)

if(NOT CMAKE_GENERATOR STREQUAL "Xcode")
    set(APPLE_PROVISIONING_PROFILE "${CMAKE_SOURCE_DIR}/embedded.provisionprofile" CACHE FILEPATH "Embedded provisioning profile")
    if (APPLE_PROVISIONING_PROFILE)
        configure_file("${APPLE_PROVISIONING_PROFILE}" "${BUNDLE_CONTENTS_PATH}/embedded.provisionprofile" COPYONLY)
    endif()
endif()

# Assets
execute_process(
    COMMAND xcrun actool --compile "${RESOURCES_OUTPUT_PATH}" --platform macosx --minimum-deployment-target ${CMAKE_OSX_DEPLOYMENT_TARGET} "${CMAKE_SOURCE_DIR}/resources/macOS/Assets.xcassets" > /dev/null 2>&1
    OUTPUT_VARIABLE VREMENAR_ASSETS_LOG
)

if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(APPLE_MACOS_ASSET_CATALOGS "${CMAKE_SOURCE_DIR}/resources/macOS/Vremenar.icns")

    configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/container-migration.plist" "${CMAKE_BINARY_DIR}/container-migration.plist" COPYONLY)
    set(APPLE_MACOS_CONTAINERMIGRATION "${CMAKE_BINARY_DIR}/container-migration.plist")

    set(APPLE_MACOS_TRANSLATIONS
        ${CMAKE_SOURCE_DIR}/resources/iOS/en.lproj
        ${CMAKE_SOURCE_DIR}/resources/iOS/de.lproj
        ${CMAKE_SOURCE_DIR}/resources/iOS/sl.lproj
    )
else()
    file(COPY "${CMAKE_SOURCE_DIR}/resources/macOS/Vremenar.icns" DESTINATION "${RESOURCES_OUTPUT_PATH}")

    configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/container-migration.plist" "${RESOURCES_OUTPUT_PATH}/container-migration.plist" COPYONLY)

    configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/en.lproj/InfoPlist.strings" "${RESOURCES_OUTPUT_PATH}/en.lproj/InfoPlist.strings" COPYONLY)
    configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/de.lproj/InfoPlist.strings" "${RESOURCES_OUTPUT_PATH}/de.lproj/InfoPlist.strings" COPYONLY)
    configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/sl.lproj/InfoPlist.strings" "${RESOURCES_OUTPUT_PATH}/sl.lproj/InfoPlist.strings" COPYONLY)
endif()

# Countly
set(COUNTLY_PATH "${CMAKE_SOURCE_DIR}/3rdparty/Countly/macOS")
find_library(Countly Countly HINTS ${COUNTLY_PATH} REQUIRED)
if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(APPLE_MACOS_EMBED_FRAMEWORKS ${Countly})
else()
    file(COPY ${Countly} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
endif()

# Firebase
if(CMAKE_GENERATOR STREQUAL "Xcode")
    configure_file("${CMAKE_SOURCE_DIR}/GoogleService-Info.plist" "${CMAKE_BINARY_DIR}/GoogleService-Info.plist" COPYONLY)
    set(APPLE_MACOS_GOOGLESERVICE "${CMAKE_BINARY_DIR}/GoogleService-Info.plist")
else()
    configure_file("${CMAKE_SOURCE_DIR}/GoogleService-Info.plist" "${RESOURCES_OUTPUT_PATH}/GoogleService-Info.plist" COPYONLY)
endif()

set(FIREBASE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/Firebase/macOS")
find_library(nanopb nanopb HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FBLPromises FBLPromises HINTS ${FIREBASE_PATH} REQUIRED)
find_library(GoogleDataTransport GoogleDataTransport HINTS ${FIREBASE_PATH} REQUIRED)
find_library(GoogleUtilities GoogleUtilities HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseCore FirebaseCore HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseCoreInternal FirebaseCoreInternal HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseInstallations FirebaseInstallations HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseMessaging FirebaseMessaging HINTS ${FIREBASE_PATH} REQUIRED)

# Sparkle
if(NOT VREMENAR_STORE)
    set(SPARKLE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/Sparkle/macOS")
    find_library(Sparkle Sparkle HINTS ${SPARKLE_PATH} REQUIRED)

    if(CMAKE_GENERATOR STREQUAL "Xcode")
        set(APPLE_MACOS_EMBED_FRAMEWORKS ${APPLE_MACOS_EMBED_FRAMEWORKS} ${Countly})
    else()
        file(COPY ${Sparkle} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
    endif()
endif()
