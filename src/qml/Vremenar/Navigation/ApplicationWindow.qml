/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.7
import QtQuick.Controls 2.2

import Vremenar 1.0
import Vremenar.Common 1.0

ApplicationWindow {
    id: app
    property ApplicationWindow applicationWindow : app
    property bool ready: false

    width: 640
    height: 480

    menuBar: MainMenu {}

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
