#
# Vremenar
# Copyright (C) 2017 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

TARGET = Vremenar

# Common configuration
include($$top_srcdir/config/version.pri)
include($$top_srcdir/config/dependencies.pri)
include($$top_srcdir/config/compiler.pri)
include($$top_srcdir/config/platform.pri)

QML_IMPORT_PATH = src/qml

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler).
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp
RESOURCES += \
    src/qml/qml.qrc \
    src/qml/Vremenar/Navigation/navigation.qrc \
    src/qml/Vremenar/Maps/maps.qrc
