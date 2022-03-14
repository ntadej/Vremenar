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
import QtQuick.Controls 2.12

import Vremenar 1.0
import Vremenar.Common 1.0

Dialog {
    id: dialog
    width: parent.width
    height: parent.height

    modal: true
    focus: true
    padding: 0
    topPadding: 0

    background: MaskedBlur {
        anchors.fill: parent
        blurSource: contentPlaceholder
        color: UI.navBarColor
        sourceX: parent.x
        sourceY: parent.y
        maskSource: Rectangle {
            width: dialog.width
            height: dialog.height
            visible: false
        }
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: UI.hoverDuration }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: UI.hoverDuration }
    }
}