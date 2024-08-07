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
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Vremenar 1.0

Dialog {
    id: dialog
    width: Math.min(parent.width - 2 * Math.max(UI.safetyMarginLeft, UI.safetyMarginRight), implicitDialogWidth)
    height: Math.min(parent.height - 2 * Math.max(UI.safetyMarginTop, UI.safetyMarginBottom), implicitDialogHeight)
    property int implicitDialogWidth: 300
    property int implicitDialogHeight: 400

    modal: true
    focus: true
    padding: 0
    topPadding: 0

    background: Item {
        Rectangle {
            id: maskSource
            color: UI.shadowColor
            radius: UI.radiusCommon
            anchors.fill: parent
            visible: false
        }

        ShadowSource {
            id: shadowSource
        }

        MaskedBlurWithShadow {
            blurSource: contentPlaceholder
            maskSource: maskSource
            shadowSource: shadowSource
            sourceX: parent.parent.x
            sourceY: parent.parent.y - (menuBar ? menuBar.height : 0)
            color: UI.navBarColor
        }
    }

    Overlay.modal: ColumnLayout {
        spacing: 0
        Rectangle {
            color: "transparent"
            height: UI.navBarHeight + UI.safetyMarginTop + (menuBar ? menuBar.height : 0)
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
