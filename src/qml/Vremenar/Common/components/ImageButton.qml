/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtGraphicalEffects 1.0

import Vremenar 1.0
import Vremenar.Common 1.0

MouseArea {
    id: button

    property alias image: image.source
    property bool active: false

    height: width
    hoverEnabled: true

    Rectangle {
        id: background
        anchors.fill: parent
        color: "transparent"
        radius: UI.radiusCommon / 2

        Image {
            id: image
            anchors.fill: parent
            anchors.margins: UI.iconBorderThickness

            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: image.width
                    height: image.height
                    radius: UI.radiusCommon / 2
                }
            }
        }
    }

    states: [
        State {
            name: "down"
            when: pressedButtons & Qt.LeftButton

            PropertyChanges {
                target: background
                color: Qt.darker(UI.buttonColor, 1.1)
            }
        },
        State {
            name: "hover"
            when: containsMouse

            PropertyChanges {
                target: background
                color: UI.buttonColor
            }
        },
        State {
            name: "active"
            when: active

            PropertyChanges {
                target: background
                color: UI.buttonColorHover
            }
        }
    ]

    transitions: Transition {
        ColorAnimation { duration: UI.hoverDuration }
    }
}
