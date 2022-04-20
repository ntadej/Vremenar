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
    URI Vremenar.Desktop
    VERSION 1.0
    QML_FILES
        +custommenu/MainMenu.qml
        +materialstyle/BaseApplicationWindow.qml
        +nativemenu/MainMenu.qml
        +universalstyle/BaseApplicationWindow.qml
        BaseApplicationWindow.qml
        MainApplicationWindow.qml
        MainMenu.qml
    RESOURCE_PREFIX Vremenar/Desktop
    RESOURCES
        qmldir
    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)
