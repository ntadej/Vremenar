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

CONFIG += qt
LOGGING = true

equals(QT_MAJOR_VERSION, 5): CONFIG += legacy
equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 15): error("Requires Qt 5.15 or later!")

# Use C++17
CONFIG += c++17

# Qt modules and other dependencies
QT += qml quick
QT += location positioning sql
QT += quickcontrols2

# Positioning
!firetv {
    CONFIG += positioning
}
positioning {
    DEFINES += VREMENAR_POSITIONING
}

# Store
store {
    DEFINES += VREMENAR_STORE
}

# Define common platforms
macos|if(linux:!android)|win32 {
    CONFIG += desktop
} else:ios|android {
    DEFINES += VREMENAR_MOBILE
    CONFIG += mobile
}

# Desktop dependencies
desktop {
    QT += widgets
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler).
DEFINES += QT_DEPRECATED_WARNINGS

# All warnings
win32:msvc {
    QMAKE_CXXFLAGS += /WX /utf-8
} else {
    QMAKE_CXXFLAGS += -Wall -Wextra -Werror -Wno-unknown-pragmas -pedantic
}

# Add GSL
INCLUDEPATH += $$top_srcdir/3rdparty/GSL/include

# Internationalisation
include($$top_srcdir/config/i18n.pri)

# Custom config
include($$top_srcdir/config.pri)
include($$top_srcdir/config/config_check.pri)

# Config summary
macos {
    message("Building for platform: macOS")
} else:linux:!android {
    message("Building for platform: Linux")
} else:win32 {
    mingw {
        message("Building for platform: Windows (MinGW)")
    } else {
        message("Building for platform: Windows (MSVC)")
    }
} else:ios {
    message("Building for platform: iOS")
} else:android {
    message("Building for platform: Android")
} else {
    error("Unknown platform '$${QMAKE_PLATFORM}'!")
}

equals(LOGGING, true) {
    message("Logging enabled")
}
