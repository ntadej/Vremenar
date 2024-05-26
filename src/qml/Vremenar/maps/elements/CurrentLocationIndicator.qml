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
import QtLocation 6.5

import Vremenar 1.0

MapQuickItem {
    anchorPoint.x: sourceItem.width / 2
    anchorPoint.y: sourceItem.width / 2
    coordinate: VLocation.position

    sourceItem: Item {
        id: sourceItem
        width: 16
        height: width

        ShadowSource {
            id: shadowSource
            radius: width / 2
        }

        CommonShadow {
            source: shadowSource
            anchors.centerIn: parent
        }

        Rectangle {
            radius: width / 2
            color: UI.colorPrimary
            border.color: "white"
            border.width: 2
            anchors.fill: parent
        }
    }

    visible: VLocation.enabled
}
