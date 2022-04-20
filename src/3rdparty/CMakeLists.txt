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

add_library(QMacToolBar OBJECT
    QMacToolBar_p.h
    QMacToolBar.h
    QMacToolBar.mm
    QMacToolBarDelegate_p.h
    QMacToolBarDelegate.mm
    QMacToolBarItem_p.h
    QMacToolBarItem.h
    QMacToolBarItem.mm
    QNSToolbar_p.h
    QNSToolbar.mm
)

target_link_libraries(QMacToolBar
    PRIVATE
        Qt::Core
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
)
