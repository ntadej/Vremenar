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

# Mapbox GL plugin requirement
QT += sql

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
equals(ANDROID_TARGET_ARCH,x86) {
    ANDROID_EXTRA_LIBS = \
        $$top_srcdir/3rdparty/openssl-android-x86/libcrypto.so \
        $$top_srcdir/3rdparty/openssl-android-x86/libssl.so
}
equals(ANDROID_TARGET_ARCH,x86_64) {
    ANDROID_EXTRA_LIBS = \
        $$top_srcdir/3rdparty/openssl-android-x86_64/libcrypto.so \
        $$top_srcdir/3rdparty/openssl-android-x86_64/libssl.so
}
equals(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$top_srcdir/3rdparty/openssl-android-armeabi-v7a/libcrypto.so \
        $$top_srcdir/3rdparty/openssl-android-armeabi-v7a/libssl.so
}
equals(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_EXTRA_LIBS = \
        $$top_srcdir/3rdparty/openssl-android-arm64-v8a/libcrypto.so \
        $$top_srcdir/3rdparty/openssl-android-arm64-v8a/libssl.so
}
