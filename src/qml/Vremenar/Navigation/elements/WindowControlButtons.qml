/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
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
import Vremenar.Common 1.0

Row {
    WindowButton {
        id: minimizeButton
        icon: UI.customWindowButtons ? "minimize" : ""
        family: UI.iconTheme
        onClicked: {
            app.showMinimized()
        }
    }

    WindowButton {
        id: maximizeButton
        icon: UI.customWindowButtons ? (app.visibility === Window.Maximized ? "restore" : "maximize") : ""
        family: UI.iconTheme
        onClicked: {
            app.toggleMaximized()
        }
    }

    WindowButton {
        id: closeButton
        icon: UI.customWindowButtons ? "close" : ""
        family: UI.iconTheme
        special: true
        onClicked: {
            app.close()
        }
    }
}
