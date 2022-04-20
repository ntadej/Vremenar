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

qt_add_qml_module(Vremenar
    URI Vremenar.Fonts
    VERSION 1.0
    QML_FILES
        Loader.qml
        +materialstyle/Loader.qml
    RESOURCE_PREFIX Vremenar/Fonts
    RESOURCES
      qmldir
    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)

if(NOT MOBILE OR iOS)
    qt_add_resources(Vremenar fonts_Ionicons
        PREFIX
            /Vremenar/Fonts
        FILES
            data/Ionicons.ttf
    )
endif()

if(ANDROID)
    qt_add_resources(Vremenar fonts_Material
        PREFIX
            /Vremenar/Fonts
        FILES
            data/MaterialIcons-Regular.ttf
            data/MaterialIconsOutlined-Regular.otf
    )
endif()
