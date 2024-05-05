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

import Vremenar 1.0

MouseArea {
    id: button

    property alias icon: iconObject.icon
    property alias family: iconObject.family
    property alias size: iconObject.size
    property bool disabled: false

    signal confirmed()

    height: width

    enabled: !disabled
    hoverEnabled: !disabled

    Keys.onReturnPressed: confirmed()
    Keys.onEnterPressed: confirmed()

    Rectangle {
        id: background
        anchors.fill: parent
        color: "transparent"

        Icon {
            id: iconObject
            anchors.fill: parent
            size: UI.iconSizeCommon
            color: UI.buttonColor
        }
    }

    states: [
        State {
            name: "down"
            when: pressedButtons & Qt.LeftButton

            PropertyChanges {
                target: iconObject
                color: Qt.darker(UI.buttonColorHover, 1.1)
            }
        },
        State {
            name: "hover"
            when: containsMouse || focus

            PropertyChanges {
                target: iconObject
                color: UI.buttonColorHover
            }
        },
        State {
            name: "disabled"
            when: disabled

            PropertyChanges {
                target: iconObject
                color: UI.buttonColorDisabled
            }
        }

    ]

    transitions: Transition {
        ColorAnimation { duration: UI.hoverDuration }
    }

    function downAnimation() {
        if (disabled || containsMouse)
            return

        state = "down"
        timer.restart()
    }

    Timer {
        id: timer
        interval: UI.hoverDuration; running: false; repeat: false
        onTriggered: {
            if (focus) {
                button.state = "hover"
            } else if (disabled) {
                button.state = "disabled"
            } else  {
                button.state = ""
            }
        }
    }
}
