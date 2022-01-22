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

# Private module for the safe area margins and icons
QT += gui-private

# Ignore some warnings on iOS
ios {
    QMAKE_CXXFLAGS += -Wno-shorten-64-to-32 -Wno-unused-command-line-argument
}

# Define substitution files
iOSPlist.input = $$top_srcdir/resources/iOS/Info.plist.in
iOSPlist.output = $$OUT_PWD/Info.plist
QMAKE_SUBSTITUTES += iOSPlist

store {
    iOSExport.input = $$top_srcdir/resources/iOS/AppStoreExport.plist.in
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
