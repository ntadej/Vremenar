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

# Installation rules
target.path = /usr/bin

# Install desktop file
desktop.path = /usr/share/applications
desktop.files = $$top_srcdir/resources/Linux/vremenar.desktop


# Install icons
icons_16.path = /usr/share/icons/hicolor/16x16/apps
icons_16.files = $$top_srcdir/resources/Linux/logo/16x16/vremenar.png

icons_24.path = /usr/share/icons/hicolor/24x24/apps
icons_24.files = $$top_srcdir/resources/Linux/logo/24x24/vremenar.png

icons_32.path = /usr/share/icons/hicolor/32x32/apps
icons_32.files = $$top_srcdir/resources/Linux/logo/32x32/vremenar.png

icons_48.path = /usr/share/icons/hicolor/48x48/apps
icons_48.files = $$top_srcdir/resources/Linux/logo/48x48/vremenar.png

icons_64.path = /usr/share/icons/hicolor/64x64/apps
icons_64.files = $$top_srcdir/resources/Linux/logo/64x64/vremenar.png

icons_128.path = /usr/share/icons/hicolor/128x128/apps
icons_128.files = $$top_srcdir/resources/Linux/logo/128x128/vremenar.png

icons_256.path = /usr/share/icons/hicolor/256x256/apps
icons_256.files = $$top_srcdir/resources/Linux/logo/256x256/vremenar.png

INSTALLS += target desktop \
    icons_16 icons_24 icons_32 icons_48 icons_64 icons_128 icons_256
