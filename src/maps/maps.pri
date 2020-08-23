#
# Vremenar
# Copyright (C) 2020 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

SOURCES += \
    src/maps/LocationProvider.cpp \
    src/maps/MapsCommon.cpp \
    src/maps/MapsManager.cpp

HEADERS += \
    src/maps/LocationProvider.h \
    src/maps/LocationProviderPlatform.h \
    src/maps/MapsCommon.h \
    src/maps/MapsManager.h

# macOS/iOS specific
macx|ios {
    HEADERS += \
        src/maps/LocationProviderMacOSiOS.h

    OBJECTIVE_SOURCES += \
        src/maps/LocationProviderMacOSiOS.mm
}
