#
# Vremenar
# Copyright (C) 2019 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#
# Android extras
QT += androidextras

# Manifest defines
!defaultmanifest {
    VREMENAR_ANDROID_PERMISSIONS = '<uses-permission android:name="android.permission.INTERNET" />' \
        '<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />' \
        '<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />'

    positioning {
        VREMENAR_ANDROID_FEATURES += '<uses-feature android:name="android.hardware.location.gps" android:required="false" />'
        VREMENAR_ANDROID_PERMISSIONS += '<uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />'
    }
} else {
    VREMENAR_ANDROID_PERMISSIONS = '<!-- %%INSERT_PERMISSIONS -->'
    VREMENAR_ANDROID_FEATURES = '<!-- %%INSERT_FEATURES -->'
}

# Define substitution files
iOSPlist.input = $$top_srcdir/resources/Android/AndroidManifest.xml.in
iOSPlist.output = $$top_srcdir/resources/Android/output/AndroidManifest.xml
QMAKE_SUBSTITUTES += iOSPlist

# Android packaging
DISTFILES += \
    $$top_srcdir/resources/Android/output/AndroidManifest.xml \
    $$top_srcdir/resources/Android/output/res/values/libs.xml \
    $$top_srcdir/resources/Android/output/res/values/styles.xml \
    $$top_srcdir/resources/Android/output/build.gradle \
    $$top_srcdir/resources/Android/output/src/org/qtproject/qt5/android/bindings/VremenarActivity.java

ANDROID_PACKAGE_SOURCE_DIR = \
        $$top_srcdir/resources/Android/output

# OpenSSL
include($$top_srcdir/3rdparty/android_openssl/openssl.pri)
