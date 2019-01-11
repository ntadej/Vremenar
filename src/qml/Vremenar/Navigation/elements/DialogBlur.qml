/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.1
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1

import Vremenar 1.0
import Vremenar.Common 1.0

Dialog {
    id: dialog
    width: Math.min(parent.width, 300)
    height: Math.min(parent.height, 400)

    modal: true
    padding: 0

    background: MaskedBlur {
        blurSource: contentPlaceholder
        color: UI.navBarColor
        sourceX: parent.x
        sourceY: parent.y
        maskSource: Rectangle {
            width: dialog.width
            height: dialog.height
            radius: UI.radiusCommon
            visible: false
        }
    }

    Overlay.modal: ColumnLayout {
        spacing: 0
        Rectangle {
            color: "transparent"
            height: UI.navBarHeight
            Layout.fillWidth: true
        }
        Rectangle {
            color: UI.navBarColor
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Behavior on opacity { NumberAnimation { duration: UI.hoverDuration } }
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: UI.hoverDuration }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: UI.hoverDuration }
    }
}
