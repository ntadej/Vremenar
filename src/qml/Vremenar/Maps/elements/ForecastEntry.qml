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
import QtLocation 5.12

import Vremenar 1.0
import Vremenar.Common 1.0

MapQuickItem {
    property string icon
    property string title

    anchorPoint.x: entry.width / 2
    anchorPoint.y: entry.width / 2

    sourceItem: Item {
        id: entry
        width: 48
        height: width
        opacity: 0

        Image {
            id: image
            anchors.centerIn: parent
            anchors.alignWhenCentered: true
            source: "../icons/" + icon + ".png"
        }

        Component.onCompleted: opacity = 1

        Behavior on opacity { PropertyAnimation { duration: 200 } }
    }
}
