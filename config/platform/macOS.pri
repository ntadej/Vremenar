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
# Private module for the icons
QT += gui-private
# Extra libraries
!legacy {
    QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64
}
LIBS += -weak_framework ApplicationServices -weak_framework Cocoa -weak_framework CoreLocation

# Deployment target and rpath
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14
QMAKE_RPATHDIR = @executable_path/../Frameworks

# Info.plist & deployment
macOSPlist.input = $$top_srcdir/resources/macOS/Info.plist.qmake.in
macOSPlist.output = $$OUT_PWD/Info.plist
QMAKE_SUBSTITUTES += macOSPlist

macOSEntitlements.input = $$top_srcdir/resources/macOS/Vremenar.entitlements.qmake.in
macOSEntitlements.output = $$OUT_PWD/Vremenar.entitlements
QMAKE_SUBSTITUTES += macOSEntitlements

!ci {
    macOSProvisioning.files = $$top_srcdir/embedded.provisionprofile
    macOSProvisioning.path = Contents
    QMAKE_BUNDLE_DATA += macOSProvisioning
}

# Assets
QMAKE_ASSET_CATALOGS += $$top_srcdir/resources/macOS/Assets.xcassets
QMAKE_INFO_PLIST = $$OUT_PWD/Info.plist
ICON = $$top_srcdir/resources/macOS/Vremenar.icns

containerMigration.files = $$top_srcdir/resources/macOS/container-migration.plist
containerMigration.path = Contents/Resources
QMAKE_BUNDLE_DATA += containerMigration

TRANSLATE_en.files = $$top_srcdir/resources/macOS/en.lproj/InfoPlist.strings
TRANSLATE_en.path = Contents/Resources/en.lproj
QMAKE_BUNDLE_DATA += TRANSLATE_en

TRANSLATE_de.files = $$top_srcdir/resources/macOS/de.lproj/InfoPlist.strings
TRANSLATE_de.path = Contents/Resources/de.lproj
QMAKE_BUNDLE_DATA += TRANSLATE_de

TRANSLATE_sl.files = $$top_srcdir/resources/macOS/sl.lproj/InfoPlist.strings
TRANSLATE_sl.path = Contents/Resources/sl.lproj
QMAKE_BUNDLE_DATA += TRANSLATE_sl

# Countly
QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Countly/macOS
LIBS += -F$$top_srcdir/3rdparty/Countly/macOS -framework Countly

countly.files = $$top_srcdir/3rdparty/Countly/macOS/Countly.framework
countly.path = Contents/Frameworks
QMAKE_BUNDLE_DATA += countly

# Firebase
!ci {
    firebase_config.files = $$top_srcdir/GoogleService-Info.plist
    firebase_config.path = Contents/Resources
    QMAKE_BUNDLE_DATA += firebase_config
}

QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Firebase/macOS
# these are static frameworks
LIBS += -F$$top_srcdir/3rdparty/Firebase/macOS \
    -ObjC \
    -framework nanopb \
    -framework PromisesObjC \
    -framework GoogleDataTransport \
    -framework GoogleUtilities \
    -framework FirebaseCore \
    -framework FirebaseInstallations \
    -framework FirebaseMessaging

# Sparkle
!store {
    QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Sparkle/macOS
    LIBS += -F$$top_srcdir/3rdparty/Sparkle/macOS -framework Sparkle

    sparkle.files = $$top_srcdir/3rdparty/Sparkle/macOS/Sparkle.framework
    sparkle.path = Contents/Frameworks
    QMAKE_BUNDLE_DATA += sparkle
}
