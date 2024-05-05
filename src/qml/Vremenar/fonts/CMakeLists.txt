#
# Vremenar
# Copyright (C) 2024 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

if(NOT MOBILE OR IOS)
    qt_add_resources(
        Vremenar
        fonts_Ionicons
        PREFIX
            /Vremenar/fonts
        FILES
            data/Ionicons.ttf
    )
endif()

if(ANDROID)
    qt_add_resources(
        Vremenar
        fonts_Material
        PREFIX
            /Vremenar/fonts
        FILES
            data/MaterialIcons-Regular.ttf
            data/MaterialIconsOutlined-Regular.otf
    )
endif()
