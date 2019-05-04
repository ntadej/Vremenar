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

SOURCES += \
    src/application/ApplicationWindow.cpp \
    src/application/BaseApplication.cpp \

HEADERS += \
    src/application/ApplicationWindow.h \
    src/application/BaseApplication.h

# Desktop specific
macx|linux {
    SOURCES += \
        src/application/DesktopApplication.cpp \
        src/application/SingleApplication.cpp \
        src/application/TrayIcon.cpp

    HEADERS += \
        src/application/DesktopApplication.h \
        src/application/SingleApplication.h \
        src/application/TrayIcon.h
}

# Mobile specific
ios|android {
    SOURCES += \
        src/application/MobileApplication.cpp

    HEADERS += \
        src/application/MobileApplication.h
}

# macOS specific
macx {
    OBJECTIVE_SOURCES += \
        src/application/DesktopApplicationMacOS.mm
}
