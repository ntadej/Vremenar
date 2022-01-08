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
    id: button

    property alias icon: iconObject.icon
    property alias family: iconObject.family
    property alias size: iconObject.size
    property bool disabled: false
    property bool special: false

    signal confirmed()

    width: UI.windowButtonWidth
    height: UI.windowButtonHeight

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
            size: UI.windowButtonIconSize
            color: UI.textColor
        }
    }

    states: [
        State {
            name: "down"
            when: pressedButtons & Qt.LeftButton

            PropertyChanges {
                target: iconObject
                color: button.special && UI.theme === Vremenar.Common.LightTheme ? UI.textColorInverted : UI.textColor
            }

            PropertyChanges {
                target: background
                color: button.special ? Qt.lighter(UI.windowButtonSpecialColor, 1.1) : UI.windowButtonDownColor
            }
        },
        State {
            name: "hover"
            when: containsMouse || focus

            PropertyChanges {
                target: iconObject
                color: button.special && UI.theme === Vremenar.Common.LightTheme ? UI.textColorInverted : UI.textColor
            }

            PropertyChanges {
                target: background
                color: button.special ? UI.windowButtonSpecialColor : UI.windowButtonHoverColor
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
            } else  {
                button.state = ""
            }
        }
    }
}
