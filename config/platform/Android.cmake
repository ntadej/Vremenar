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

# Manifest defines
if(VREMENAR_POSITIONING)
    set(VREMENAR_ANDROID_FEATURES [=[<uses-feature android:name="android.hardware.location.gps" android:required="false" />]=])
    set(VREMENAR_ANDROID_PERMISSIONS [=[<uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />]=])
else()
    set(VREMENAR_ANDROID_FEATURES "")
    set(VREMENAR_ANDROID_PERMISSIONS [=[<uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />]=])
endif()

# Define substitution files
configure_file("${CMAKE_SOURCE_DIR}/resources/Android/AndroidManifest.xml.in" "${CMAKE_SOURCE_DIR}/resources/Android/output/AndroidManifest.xml" @ONLY)

# OpenSSL
include(${CMAKE_SOURCE_DIR}/3rdparty/android_openssl/android_openssl.cmake)
