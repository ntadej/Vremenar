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

# Add QML imports
QML_IMPORT_PATH = $$top_srcdir/src/qml

SOURCES += \
    src/qml/Globals.cpp \
    src/qml/Qml.cpp \
    src/qml/UIManager.cpp \
    src/qml/UIColors.cpp \
    src/qml/UIDimensions.cpp \
    src/qml/UIEffects.cpp \
    src/qml/UITexts.cpp

HEADERS += \
    src/qml/Globals.h \
    src/qml/Qml.h \
    src/qml/UIManager.h

# iOS specific
ios {
    OBJECTIVE_SOURCES += \
       src/qml/UIManagerIOS.mm
}

# Define resources
RESOURCES += \
    src/qml/Vremenar/vremenar.qrc \
    src/qml/Vremenar/Common/common.qrc \
    src/qml/Vremenar/Common/fonts.qrc \
    src/qml/Vremenar/Maps/maps.qrc \
    src/qml/Vremenar/Navigation/navigation.qrc

# Desktop resources
macx|linux {
    RESOURCES += \
        src/qml/Vremenar/Desktop/desktop.qrc
}

# Mobile resources
ios|android {
    RESOURCES += \
        src/qml/Vremenar/Mobile/mobile.qrc
}
