#
# Vremenar
# Copyright (C) 2017 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

QMAKE_INFO_PLIST = $$top_srcdir/resources/iOS/Info.plist
ios_icon.files = $$files($$top_srcdir/resources/iOS/logo/*.png)
QMAKE_BUNDLE_DATA += ios_icon
