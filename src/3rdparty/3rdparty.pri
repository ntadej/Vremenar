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

# macOS specific
macos {
    OBJECTIVE_SOURCES += \
        src/3rdparty/QMacToolBar.mm \
        src/3rdparty/QMacToolBarItem.mm \
        src/3rdparty/QMacToolBarDelegate.mm \
        src/3rdparty/QNSToolbar.mm

    HEADERS += \
        src/3rdparty/QMacToolBar.h \
        src/3rdparty/QMacToolBar_p.h \
        src/3rdparty/QMacToolBarItem.h \
        src/3rdparty/QMacToolBarItem_p.h \
        src/3rdparty/QMacToolBarDelegate_p.h \
        src/3rdparty/QNSToolbar_p.h
}
