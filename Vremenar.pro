#
# Vremenar
# Copyright (C) 2017 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

TARGET = Vremenar
CONFIG += qt

# Common configuration
include($$top_srcdir/config/version.pri)
include($$top_srcdir/config/dependencies.pri)
include($$top_srcdir/config/compiler.pri)
include($$top_srcdir/config/platform.pri)
include($$top_srcdir/config/i18n.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler).
DEFINES += QT_DEPRECATED_WARNINGS

# Enable logging
DEFINES += LOGGING=$$LOGGING

# Add QML imports
QML_IMPORT_PATH = src/qml

# Define sources and headers
INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/application/ApplicationWindow.cpp \
    src/application/DesktopApplication.cpp \
    src/application/SingleApplication.cpp \
    src/common/Common.cpp \
    src/common/LocaleManager.cpp \
    src/common/LocalServer.cpp \
    src/common/Log.cpp \
    src/common/Resources.cpp \
    src/common/Output.cpp \
    src/qml/Globals.cpp \
    src/qml/Qml.cpp \
    src/settings/Settings.cpp \
    src/settings/SettingsDefaults.cpp \
    src/settings/SettingsDialog.cpp \
    src/settings/SettingsKeys.cpp

mac {
    OBJECTIVE_SOURCES += src/settings/SettingsDialogMacOS.mm
}

HEADERS += \
    src/application/ApplicationWindow.h \
    src/application/DesktopApplication.h \
    src/application/SingleApplication.h \
    src/common/Common.h \
    src/common/LocaleManager.h \
    src/common/LocalServer.h \
    src/common/Log.h \
    src/common/Resources.h \
    src/common/Output.h \
    src/qml/Globals.h \
    src/qml/Qml.h \
    src/settings/Settings.h \
    src/settings/SettingsDialog.h

FORMS += \
    src/settings/SettingsDialog.ui

# Define resources
RESOURCES += \
    $$top_builddir/i18n.qrc \
    src/qml/qml.qrc \
    src/qml/Vremenar/vremenar.qrc \
    src/qml/Vremenar/Common/common.qrc \
    src/qml/Vremenar/Maps/maps.qrc \
    src/qml/Vremenar/Navigation/navigation.qrc \
    resources/icons/icons.qrc \
