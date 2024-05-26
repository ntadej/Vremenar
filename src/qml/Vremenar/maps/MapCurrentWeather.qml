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

import Vremenar 1.0

Item {
    visible: !UI.mapOnly
    width: Math.ceil(UI.paddingSmall * 3 + icon.width + textTemperature.width)
    height: Math.ceil(UI.paddingSmall * 4 + UI.mapIconSizeHeight + Math.round(textLocation.height))

    opacity: VCurrent.station ? 1 : 0

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
        sourceX: parent.x
        sourceY: parent.y
        color: UI.navBarColor
    }

    TextCore {
        id: textLocation
        padding: 0
        text: VCurrent.station ? VCurrent.station.displayCurrent : ""
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        wrapMode: Text.WordWrap
        font.weight: Font.DemiBold
        font.pixelSize: UI.textCommon
        anchors {
            top: parent.top
            topMargin: UI.paddingSmall
            left: parent.left
            leftMargin: UI.paddingSmall
            right: parent.right
            rightMargin: UI.paddingSmall
        }
    }


    Image {
        id: icon
        source: VCurrent.condition ? "/Vremenar/Weather/Map/" + VCurrent.condition.icon + ".png" : ""
        width: UI.mapIconSize
        height: UI.mapIconSize
        anchors {
            bottom: parent.bottom
            bottomMargin: UI.paddingSmall
            left: parent.left
            leftMargin: UI.paddingSmall
        }
    }

    TextCommon {
        id: textTemperature
        text: VCurrent.condition ? VCurrent.condition.displayTemperature : ""
        font.weight: Font.DemiBold
        width: Math.max(UI.mapIconSize, contentWidth)
        height: UI.mapIconSizeHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors {
            bottom: parent.bottom
            bottomMargin: UI.paddingSmall + (UI.mapIconSize - UI.mapIconSizeHeight)
            right: parent.right
            rightMargin: UI.paddingSmall
        }
    }

    Behavior on opacity { PropertyAnimation { duration: UI.mapTimeChangeDuration } }
}
