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

SOURCES += \
    src/settings/Settings.cpp \
    src/settings/SettingsDefaults.cpp \
    src/settings/SettingsKeys.cpp

HEADERS += \
    src/settings/Settings.h

# Desktop specific
desktop {
    SOURCES += \
        src/settings/SettingsDialog.cpp

    HEADERS += \
        src/settings/SettingsDialog.h

    FORMS += \
        src/settings/SettingsDialog.ui
}

# macOS specific
macos {
    OBJECTIVE_SOURCES += \
        src/settings/SettingsDialogMacOS.mm
}
