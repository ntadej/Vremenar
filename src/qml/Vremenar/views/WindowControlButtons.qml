/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtQuick.Window 2.12

import Vremenar 1.0

Row {
    WindowButton {
        id: minimizeButton
        icon: UI.customWindowButtons ? "minimize" : ""
        family: UI.iconTheme
        active: app.active
        onClicked: {
            app.showMinimized()
        }
    }

    WindowButton {
        id: maximizeButton
        icon: UI.customWindowButtons ? (app.visibility === Window.Maximized ? "restore" : "maximize") : ""
        family: UI.iconTheme
        active: app.active
        onClicked: {
            app.toggleMaximized()
        }
    }

    WindowButton {
        id: closeButton
        icon: UI.customWindowButtons ? "close" : ""
        family: UI.iconTheme
        active: app.active
        special: true
        onClicked: {
            app.close()
        }
    }
}
