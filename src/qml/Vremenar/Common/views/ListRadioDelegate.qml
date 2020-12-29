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
import QtQuick.Controls 2.12

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

RadioDelegate {
    property int count
    property bool translatable: false

    id: control
    height: UI.rowHeight
    padding: UI.paddingCommon

    contentItem: TextCommon {
        text: control.translatable ? qsTr(control.text) : control.text
        opacity: enabled ? 1.0 : 0.3
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    indicator: TextIcon {
        icon: UI.iconPrefix + "checkmark"
        font.family: UI.iconTheme
        x: control.width - width - control.rightPadding
        y: parent.height / 2 - height / 2
        color: UI.theme === Vremenar.Common.LightTheme ? UI.colorPrimaryDark : UI.colorPrimary
        visible: control.checked
    }

    background: Rectangle {
        id: backgroundRectangle
        height: parent.height
        color: "transparent"

        CommonLine {
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                leftMargin: model.index != control.count - 1 ? control.leftPadding : 0
            }
        }
    }

    states: [
        State {
            name: "down"
            when: control.down

            PropertyChanges {
                target: backgroundRectangle
                color: Qt.darker(UI.hoverColor, 1.1)
            }
        },
        State {
            name: "active"
            when: control.highlighted

            PropertyChanges {
                target: backgroundRectangle
                color: UI.hoverColor
            }
        }
    ]

    transitions: Transition {
        ColorAnimation { duration: UI.hoverDuration / 2 }
    }
}
