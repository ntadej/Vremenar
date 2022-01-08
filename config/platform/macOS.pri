#
# Vremenar
# Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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
QT += macextras
LIBS += -weak_framework ApplicationServices -weak_framework Cocoa -weak_framework CoreLocation

# Deployment target and rpath
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13
QMAKE_RPATHDIR = @executable_path/../Frameworks

# Info.plist & icons
macOSPlist.input = $$top_srcdir/resources/macOS/Info.plist.in
macOSPlist.output = $$OUT_PWD/Info.plist
QMAKE_SUBSTITUTES += macOSPlist
QMAKE_INFO_PLIST = $$OUT_PWD/Info.plist
ICON = $$top_srcdir/resources/macOS/Vremenar.icns
QMAKE_ASSET_CATALOGS += $$top_srcdir/resources/macOS/Assets.xcassets

# Countly
QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Countly/macOS
LIBS += -F$$top_srcdir/3rdparty/Countly/macOS -framework Countly

countly.files = $$top_srcdir/3rdparty/Countly/macOS/Countly.framework
countly.path = Contents/Frameworks
QMAKE_BUNDLE_DATA += countly

# Sparkle
QMAKE_CXXFLAGS += -F$$top_srcdir/3rdparty/Sparkle/macOS
LIBS += -F$$top_srcdir/3rdparty/Sparkle/macOS -framework Sparkle

sparkle.files = $$top_srcdir/3rdparty/Sparkle/macOS/Sparkle.framework
sparkle.path = Contents/Frameworks
QMAKE_BUNDLE_DATA += sparkle
