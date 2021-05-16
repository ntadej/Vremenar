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

macx: include(platform/macOS.pri)
linux:!android: include(platform/Linux.pri)
win32:mingw: include(platform/Windows.pri)
ios: include(platform/iOS.pri)
android: include(platform/Android.pri)
