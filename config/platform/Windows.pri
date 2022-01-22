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

win32-g++ {
    LIBS += -luser32 -ldwmapi
}

win32-msvc {
    LIBS += user32.lib dwmapi.lib
}

QMAKE_TARGET_COMPANY = "Tadej Novak"
QMAKE_TARGET_DESCRIPTION = "Vremenar Weather"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2022 Tadej Novak"

RC_ICONS = $$top_srcdir/resources/Windows/vremenar.ico

# Define substitution files
SetupFile.input = $$top_srcdir/resources/Windows/setup.iss.in
SetupFile.output = $$OUT_PWD/setup.iss
QMAKE_SUBSTITUTES += SetupFile

OTHER_FILES += \
    $$top_srcdir/resources/Windows/setup.iss.in

# Sparkle
!store {
    QMAKE_CXXFLAGS += -I$$top_srcdir/3rdparty/Sparkle/Windows/include
    LIBS += -L$$top_srcdir/3rdparty/Sparkle/Windows/lib -lWinSparkle
}
