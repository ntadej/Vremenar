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

# macOS specific
macos {
    OBJECTIVE_SOURCES += \
        src/qml/UIManagerMacOS.mm
}

# iOS specific
ios {
    OBJECTIVE_SOURCES += \
        src/qml/UIManagerIOS.mm
}

# Android specific
android {
    SOURCES += \
        src/qml/UIManagerAndroid.cpp
}

# Define resources
RESOURCES += \
    src/qml/Vremenar/vremenar.qrc \
    src/qml/Vremenar/Common/common.qrc \
    src/qml/Vremenar/Fonts/fonts.qrc \
    src/qml/Vremenar/Maps/maps.qrc \
    src/qml/Vremenar/Navigation/navigation.qrc

!legacy {
    RESOURCES += \
        src/qml/Vremenar/Common/common6.qrc
} else {
    RESOURCES += \
        src/qml/Vremenar/Common/components/+legacy/common5.qrc
}

# Desktop resources
desktop {
    RESOURCES += \
        src/qml/Vremenar/Desktop/desktop.qrc \
        src/qml/Vremenar/Fonts/fonts_Ionicons.qrc
}

# Mobile resources
mobile {
    RESOURCES += \
        src/qml/Vremenar/Mobile/mobile.qrc
}

# Android resources
android {
    RESOURCES += \
        src/qml/Vremenar/Fonts/fonts_Material.qrc
}

# iOS resources
ios {
    RESOURCES += \
        src/qml/Vremenar/Fonts/fonts_Ionicons.qrc
}
