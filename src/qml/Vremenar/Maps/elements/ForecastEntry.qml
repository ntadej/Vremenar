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
import QtLocation 5.12

import Vremenar 1.0
import Vremenar.Common 1.0

MapQuickItem {
    property string icon
    property string title
    property int temperature
    property int temperatureLow

    anchorPoint.x: entry.width / 2
    anchorPoint.y: entry.width / 2

    sourceItem: Item {
        id: entry
        width: UI.mapIconSize
        height: UI.mapIconSize
        opacity: 0

        Image {
            id: image
            anchors.centerIn: parent
            anchors.alignWhenCentered: true
            source: "../icons/" + icon + ".png"
        }

        TextCommonShadow {
            id: textTemperature
            text: temperature
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top
            anchors.left: parent.right
            height: textTemperatureLow.visible ? parent.height / 2 : parent.height
            width: textTemperatureLow.visible ? Math.max(textTemperature.contentWidth, textTemperatureLow.contentWidth) : textTemperature.contentWidth
        }

        TextCommonShadow {
            id: textTemperatureLow
            color: UI.textColorDisabled
            text: temperatureLow
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignTop
            anchors.bottom: parent.bottom
            anchors.left: parent.right
            height: parent.height / 2
            width: textTemperature.width
            visible: temperatureLow != -1000
        }

        Component.onCompleted: opacity = 1

        Behavior on opacity { PropertyAnimation { duration: UI.mapIconFadeDuration } }
    }
}
