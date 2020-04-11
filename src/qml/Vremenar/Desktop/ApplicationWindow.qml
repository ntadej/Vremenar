/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls

import Vremenar 1.0
import QtQuick.Controls.Material 2.12

Controls.ApplicationWindow {
    id: app

    property Controls.ApplicationWindow applicationWindow : app
    property alias mainMenu: mainMenu
    property bool ready: false

    Material.theme: Material.Dark
    Material.accent: UI.colorPrimaryDark
    Material.primary: UI.colorPrimary

    width: 640
    height: 480

    menuBar: MainMenu {
        id: mainMenu
    }

    onClosing: {
        hide()
        close.accepted = false
    }

    Component.onCompleted: {
        if (Settings.rememberSize) {
            console.log("Restoring size:", Settings.width, Settings.height)

            width = Settings.width
            height = Settings.height
        }

        if (Settings.rememberPosition) {
            console.log("Restoring position:", Settings.posX, Settings.posY)

            x = Settings.posX
            y = Settings.posY
        }

        Vremenar.startCompleted()
        ready = true
    }
}
