/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtLocation 5.12

import Vremenar 1.0
import Vremenar.Common 1.0

MapQuickItem {
    anchorPoint.x: sourceItem.width / 2
    anchorPoint.y: sourceItem.width / 2
    coordinate: VLocation.position

    sourceItem: Item {
        id: sourceItem
        width: 16
        height: width

        Rectangle {
            id: rectangle
            anchors.fill: parent
            radius: width / 2
            color: UI.colorPrimary
            border.color: "white"
            border.width: 2
            visible: false
        }

        CommonShadow {
            source: rectangle
        }
    }

    visible: VLocation.enabled
}
