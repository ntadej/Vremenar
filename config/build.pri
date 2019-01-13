#
# Vremenar
# Copyright (C) 2019 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

# Use C++14
CONFIG += c++14

# Qt modules and other dependencies
QT += qml quick
QT += location positioning
QT += quickcontrols2

macx {
    QT += widgets
    QT += macextras
    LIBS += -weak_framework ApplicationServices -weak_framework Cocoa
}

ios {
    # Private module for the safe area margins
    QT += gui-private
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler).
DEFINES += QT_DEPRECATED_WARNINGS

# All warnings
QMAKE_CXXFLAGS += -Wall -Wextra -Wno-unknown-pragmas -pedantic

# Define mobile
ios|android {
    DEFINES += VREMENAR_MOBILE
}

# Custom config
include($$top_srcdir/config.pri)

ConfigFile.input = $$top_srcdir/src/Config.h.in
ConfigFile.output = $$OUT_PWD/Config.h
QMAKE_SUBSTITUTES += ConfigFile

HEADERS += $$ConfigFile.output

# Config summary
macx {
    message("Building for platform: macOS")
} else:ios {
    message("Building for platform: iOS")
} else:android {
    message("Building for platform: Android")
} else {
    error("Unknown platform!")
}

equals(LOGGING, 1) {
    message("Logging enabled")
}
