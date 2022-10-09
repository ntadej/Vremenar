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

forsimulator {
    ACTIVE_MAC_SDK=iphonesimulator
} else {
    ACTIVE_MAC_SDK=iphoneos
}

message("Building for $$ACTIVE_MAC_SDK")

# Private module for the safe area margins and icons
QT += gui-private

# Ignore some warnings on iOS
QMAKE_CXXFLAGS += -Wno-shorten-64-to-32 -Wno-unused-command-line-argument
# qmake seems to require Qt main wrapper with Qt6
!legacy {
    LIBS += -Wl,-e,_qt_main_wrapper
}

# Define substitution files
iOSPlist.input = $$top_srcdir/resources/iOS/Info.plist.qmake.in
iOSPlist.output = $$OUT_PWD/Info.plist
QMAKE_SUBSTITUTES += iOSPlist

iOSEntitlements.input = $$top_srcdir/resources/iOS/Vremenar.entitlements.qmake.in
iOSEntitlements.output = $$OUT_PWD/Vremenar.entitlements
QMAKE_SUBSTITUTES += iOSEntitlements

iOSEntitlementsSettings.name = CODE_SIGN_ENTITLEMENTS
iOSEntitlementsSettings.value = $$OUT_PWD/Vremenar.entitlements
QMAKE_MAC_XCODE_SETTINGS += iOSEntitlementsSettings

store {
    iOSExport.input = $$top_srcdir/resources/iOS/AppStoreExport.plist.qmake.in
    iOSExport.output = $$OUT_PWD/AppStoreExport.plist
    QMAKE_SUBSTITUTES += iOSExport
}

# Info.plist
QMAKE_TARGET_BUNDLE_PREFIX = si.tano
QMAKE_INFO_PLIST = $$OUT_PWD/Info.plist

QMAKE_ASSET_CATALOGS += $$top_srcdir/resources/iOS/Assets.xcassets

launch_storyboard.files = $$top_srcdir/resources/iOS/VremenarLaunchScreen.storyboard
QMAKE_BUNDLE_DATA += launch_storyboard

TRANSLATE_en.files = $$top_srcdir/resources/iOS/en.lproj/InfoPlist.strings
TRANSLATE_en.path = en.lproj
QMAKE_BUNDLE_DATA += TRANSLATE_en

TRANSLATE_de.files = $$top_srcdir/resources/iOS/de.lproj/InfoPlist.strings
TRANSLATE_de.path = de.lproj
QMAKE_BUNDLE_DATA += TRANSLATE_de

TRANSLATE_sl.files = $$top_srcdir/resources/iOS/sl.lproj/InfoPlist.strings
TRANSLATE_sl.path = sl.lproj
QMAKE_BUNDLE_DATA += TRANSLATE_sl

# Firebase
!ci {
    firebase_config.files = $$top_srcdir/GoogleService-Info.plist
    QMAKE_BUNDLE_DATA += firebase_config
}

forsimulator {
    QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Firebase/iOSSimulator
    LIBS += -F$$top_srcdir/3rdparty/Firebase/iOSSimulator
} else {
    QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Firebase/iOS
    LIBS += -F$$top_srcdir/3rdparty/Firebase/iOS
}
# these are static frameworks
LIBS += -ObjC \
    -framework nanopb \
    -framework FBLPromises \
    -framework GoogleDataTransport \
    -framework GoogleUtilities \
    -framework FirebaseCoreInternal \
    -framework FirebaseCore \
    -framework FirebaseInstallations \
    -framework FirebaseMessaging
LIBS += \
    -L$(SDKROOT)/usr/lib/swift \
    -L/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/$$ACTIVE_MAC_SDK
QMAKE_RPATHDIR += /usr/lib/swift

# Countly
forsimulator {
    QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Countly/iOSSimulator
    LIBS += -F$$top_srcdir/3rdparty/Countly/iOSSimulator -framework Countly

    countly.files = $$top_srcdir/3rdparty/Countly/iOSSimulator/Countly.framework
    countly.path = Frameworks
    QMAKE_BUNDLE_DATA += countly
} else {
    QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Countly/iOS
    LIBS += -F$$top_srcdir/3rdparty/Countly/iOS -framework Countly

    countly.files = $$top_srcdir/3rdparty/Countly/iOS/Countly.framework
    countly.path = Frameworks
    QMAKE_BUNDLE_DATA += countly
}
