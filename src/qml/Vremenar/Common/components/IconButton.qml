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

import Vremenar 1.0
import Vremenar.Common 1.0

MouseArea {
    id: button

    property alias icon: textLabel.icon
    property alias family: textLabel.font.family

    height: width

    hoverEnabled: true

    Rectangle {
        id: background
        anchors.fill: parent
        color: "transparent"

        TextIcon {
            id: textLabel
            anchors.fill: parent
            font.pixelSize: UI.iconSizeCommon
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: UI.textColor
        }
    }

    states: [
        State {
            name: "down"
            when: pressedButtons & Qt.LeftButton

            PropertyChanges {
                target: textLabel
                color: Qt.darker(UI.colorPrimary, 1.1)
            }
        },
        State {
            name: "hover"
            when: containsMouse


            PropertyChanges {
                target: textLabel
                color: UI.colorPrimary
            }
        }
    ]

    transitions: Transition {
        ColorAnimation { duration: UI.hoverDuration }
    }

    function downAnimation() {
        if (containsMouse)
            return

        state = "down"
        timer.restart()
    }

    Timer {
        id: timer
        interval: UI.hoverDuration; running: false; repeat: false
        onTriggered: button.state = ""
    }
}
