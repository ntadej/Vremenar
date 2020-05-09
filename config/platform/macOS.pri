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

# Extra libraries
QT += macextras
LIBS += -weak_framework ApplicationServices -weak_framework Cocoa -weak_framework CoreLocation

# Deployment target
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12

# Info.plist & icons
QMAKE_INFO_PLIST = $$top_srcdir/resources/macOS/Info.plist
ICON = $$top_srcdir/resources/macOS/Vremenar.icns

# Countly
LIBS += -framework Countly
