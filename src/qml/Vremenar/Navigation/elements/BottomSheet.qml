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

import Vremenar 1.0
import Vremenar.Common 1.0

MouseArea {
    default property alias contents: content.children
    property alias contentItem: content
    property alias frameItem: shadowSource
    property bool fullWidth: parent.width - 2 * (UI.safetyMarginLeft + UI.safetyMarginRight) <= UI.bottomSheetMaxWidth

    height: UI.bottomSheetBaseHeight + UI.radiusCommon + UI.safetyMarginBottom
    clip: true

    Rectangle {
        id: rounded
        radius: UI.radiusCommon
        anchors.fill: parent
        visible: false
    }

    Rectangle {
        id: shadowSource
        color: UI.shadowColor
        radius: UI.radiusCommon
        anchors.fill: parent
        visible: false
    }

    MaskedBlur {
        id: blur
        color: UI.navBarColor
        maskSource: rounded
        blurSource: contentPlaceholder
        sourceX: parent.x
        sourceY: parent.y
        sourceHeight: parent.height - UI.radiusCommon
    }

    Item {
        id: content
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }
}
