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

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14")

set(BUNDLE_CONTENTS_PATH "${CMAKE_BINARY_DIR}/${VREMENAR_NAME}.app/Contents")
set(FRAMEWORKS_OUTPUT_PATH "${BUNDLE_CONTENTS_PATH}/Frameworks")
set(RESOURCES_OUTPUT_PATH "${BUNDLE_CONTENTS_PATH}/Resources")

# Deployment target and rpath
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")

configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/build_dmg.sh.in" "${CMAKE_BINARY_DIR}/build_dmg.sh" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/resign.sh.in" "${CMAKE_BINARY_DIR}/resign.sh" @ONLY)

# Info.plist & deployment
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/Info.plist.in" "${CMAKE_BINARY_DIR}/Info.plist" @ONLY)

configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/Vremenar.entitlements" "${CMAKE_BINARY_DIR}/Vremenar.entitlements" COPYONLY)
if (NOT CIBUILD)
    configure_file("${CMAKE_SOURCE_DIR}/embedded.provisionprofile" "${BUNDLE_CONTENTS_PATH}/embedded.provisionprofile" COPYONLY)
endif()

# Assets
execute_process(
    COMMAND xcrun actool --compile "${RESOURCES_OUTPUT_PATH}" --platform macosx --minimum-deployment-target ${CMAKE_OSX_DEPLOYMENT_TARGET} "${CMAKE_SOURCE_DIR}/resources/macOS/Assets.xcassets" > /dev/null 2>&1
    OUTPUT_VARIABLE VREMENAR_ASSETS_LOG
)
file(COPY "${CMAKE_SOURCE_DIR}/resources/macOS/Vremenar.icns" DESTINATION "${RESOURCES_OUTPUT_PATH}")

configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/container-migration.plist" "${RESOURCES_OUTPUT_PATH}/container-migration.plist" COPYONLY)

configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/en.lproj/InfoPlist.strings" "${RESOURCES_OUTPUT_PATH}/en.lproj/InfoPlist.strings" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/de.lproj/InfoPlist.strings" "${RESOURCES_OUTPUT_PATH}/de.lproj/InfoPlist.strings" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/resources/macOS/sl.lproj/InfoPlist.strings" "${RESOURCES_OUTPUT_PATH}/sl.lproj/InfoPlist.strings" COPYONLY)

# Countly
set(COUNTLY_PATH "${CMAKE_SOURCE_DIR}/3rdparty/Countly/macOS")
find_library(Countly Countly HINTS ${COUNTLY_PATH} REQUIRED)
file(COPY ${Countly} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")

# Firebase
if (NOT CIBUILD)
    configure_file("${CMAKE_SOURCE_DIR}/GoogleService-Info.plist" "${CMAKE_BINARY_DIR}/${VREMENAR_NAME}.app/Contents/Resources/GoogleService-Info.plist" COPYONLY)
endif()

set(FIREBASE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/Firebase/macOS")
find_library(nanopb nanopb HINTS ${FIREBASE_PATH} REQUIRED)
find_library(PromisesObjC PromisesObjC HINTS ${FIREBASE_PATH} REQUIRED)
find_library(GoogleDataTransport GoogleDataTransport HINTS ${FIREBASE_PATH} REQUIRED)
find_library(GoogleUtilities GoogleUtilities HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseCore FirebaseCore HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseInstallations FirebaseInstallations HINTS ${FIREBASE_PATH} REQUIRED)
find_library(FirebaseMessaging FirebaseMessaging HINTS ${FIREBASE_PATH} REQUIRED)
file(COPY ${nanopb} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
file(COPY ${PromisesObjC} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
file(COPY ${GoogleDataTransport} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
file(COPY ${GoogleUtilities} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
file(COPY ${FirebaseCore} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
file(COPY ${FirebaseInstallations} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
file(COPY ${FirebaseMessaging} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")

# Sparkle
if(NOT STORE)
    set(SPARKLE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/Sparkle/macOS")
    find_library(Sparkle Sparkle HINTS ${SPARKLE_PATH} REQUIRED)

    file(COPY ${Sparkle} DESTINATION "${FRAMEWORKS_OUTPUT_PATH}")
endif()
