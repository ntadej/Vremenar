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

Item {
    default property alias contents: content.children

    height: UI.bottomSheetBaseHeight + UI.radiusCommon + UI.safetyMarginBottom
    width: Math.min(parent.width, UI.bottomSheetMaxWidth)
    clip: true

    Rectangle {
        id: rounded
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
        sourceHeight: UI.bottomSheetBaseHeight
    }

    Item {
        id: content
        anchors.fill: parent
    }
}
