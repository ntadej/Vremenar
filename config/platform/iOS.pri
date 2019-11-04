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

# Private module for the safe area margins
QT += gui-private

# Info.plist
QMAKE_INFO_PLIST = $$top_srcdir/resources/iOS/Info.plist

ios_icon.files = $$files($$top_srcdir/resources/iOS/logo/*.png)
QMAKE_BUNDLE_DATA += ios_icon

launch_storyboard.files = $$top_srcdir/resources/iOS/VremenarLaunchScreen.storyboard
QMAKE_BUNDLE_DATA += launch_storyboard
