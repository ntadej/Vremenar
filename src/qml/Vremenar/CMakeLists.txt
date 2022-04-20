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
    URI Vremenar
    VERSION 1.0
    QML_FILES
        main.qml
    RESOURCE_PREFIX Vremenar
    RESOURCES
        qmldir
    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)

add_subdirectory(Common)
add_subdirectory(Fonts)
add_subdirectory(Maps)
add_subdirectory(Navigation)
if(MOBILE)
    add_subdirectory(Mobile)
else()
    add_subdirectory(Desktop)
endif()
