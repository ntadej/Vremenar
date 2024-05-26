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
    property string icon
    property string iconTmp: ""
    property string title
    property int temperature
    property int temperatureLow

    anchorPoint.x: entry.width / 2
    anchorPoint.y: entry.width / 2

    onIconChanged: {
        image.visible = true
        fadeOutAnimation.start()
        fadeInAnimation.start()
    }

    sourceItem: Item {
        id: entry
        width: UI.mapIconSize
        height: UI.mapIconSize
        opacity: 0

        Image {
            id: imageTmp
            anchors.centerIn: parent
            anchors.alignWhenCentered: true
            source: iconTmp ? "/Vremenar/Weather/Map/" + iconTmp + ".png" : ""

            NumberAnimation on opacity {
                id: fadeOutAnimation
                to: 0.5
                duration: UI.mapIconFadeDuration / 2
            }
        }

        Image {
            id: image
            anchors.centerIn: parent
            anchors.alignWhenCentered: true
            source: icon ? "/Vremenar/Weather/Map/" + icon + ".png" : ""

            NumberAnimation on opacity {
                id: fadeInAnimation
                from: 0; to: 1
                duration: UI.mapIconFadeDuration

                onRunningChanged: {
                    if (!running) {
                        iconTmp = icon
                    }
                }
            }
        }

        TextCommonShadow {
            id: textTemperature
            color: UI.textColorMap
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
            color: UI.textColorMapSecondary
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
