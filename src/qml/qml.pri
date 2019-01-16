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
    src/qml/qml.qrc \
    src/qml/Vremenar/vremenar.qrc \
    src/qml/Vremenar/Common/common.qrc \
    src/qml/Vremenar/Common/fonts.qrc \
    src/qml/Vremenar/Maps/maps.qrc \
    src/qml/Vremenar/Navigation/navigation.qrc

# Define QML files
OTHER_FILES += \
    src/qml/main.qml \
    src/qml/Vremenar/Common/qmldir \
    src/qml/Vremenar/Common/*.qml \
    src/qml/Vremenar/Common/components/*.qml \
    src/qml/Vremenar/Common/fonts/*.js \
    src/qml/Vremenar/Common/fonts/*.qml \
    src/qml/Vremenar/Common/fonts/Ionicons/*.js \
    src/qml/Vremenar/Common/menus/*.qml \
    src/qml/Vremenar/Common/menus/+custommenu/*.qml \
    src/qml/Vremenar/Common/menus/+nativemenu/*.qml \
    src/qml/Vremenar/Common/views/*.qml \
    src/qml/Vremenar/Common/text/*.qml \
    src/qml/Vremenar/Maps/qmldir \
    src/qml/Vremenar/Maps/*.qml \
    src/qml/Vremenar/Maps/elements/*.qml \
    src/qml/Vremenar/Navigation/qmldir \
    src/qml/Vremenar/Navigation/*.qml \
    src/qml/Vremenar/Navigation/+mobile/*.qml \
    src/qml/Vremenar/Navigation/elements/*.qml \
    src/qml/Vremenar/Weather/qmldir \
    src/qml/Vremenar/Weather/*.qml
