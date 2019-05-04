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

CONFIG += qt

lessThan(QT_MINOR_VERSION, 12): error("Requires Qt 5.12 or later!")

# Use C++14
CONFIG += c++14

# Qt modules and other dependencies
QT += qml quick
QT += location positioning
QT += quickcontrols2

# Desktop dependencies
macx|linux {
    QT += widgets
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler).
DEFINES += QT_DEPRECATED_WARNINGS

# All warnings
QMAKE_CXXFLAGS += -Wall -Wextra -Wno-unknown-pragmas -pedantic

# Internationalisation
include($$top_srcdir/config/i18n.pri)

# Custom config
include($$top_srcdir/config.pri)

# Config summary
macx {
    message("Building for platform: macOS")
} else:linux {
    message("Building for platform: Linux")
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
