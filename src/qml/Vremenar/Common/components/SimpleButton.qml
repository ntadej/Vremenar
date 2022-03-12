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

import Vremenar 1.0
import Vremenar.Common 1.0

MouseArea {
    property alias text: textLabel.text
    property bool disabled: false

    signal confirmed()

    enabled: !disabled
    hoverEnabled: !disabled

    Keys.onReturnPressed: confirmed()
    Keys.onEnterPressed: confirmed()

    height: textLabel.contentHeight + UI.paddingCommon / 2
    width: textLabel.contentWidth + UI.paddingCommon

    Rectangle {
        id: background
        anchors.fill: parent
        color: "transparent"

        TextCommon {
            id: textLabel
            anchors.centerIn: parent
            font.pixelSize: UI.textCommon
            color: UI.textColor
        }
    }

    states: [
        State {
            name: "down"
            when: pressedButtons & Qt.LeftButton

            PropertyChanges {
                target: textLabel
                color: Qt.darker(UI.buttonColorHover, 1.1)
            }
        },
        State {
            name: "hover"
            when: containsMouse || focus

            PropertyChanges {
                target: textLabel
                color: UI.buttonColorHover
            }
        },
        State {
            name: "disabled"
            when: disabled

            PropertyChanges {
                target: textLabel
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
