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

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    visible: !UI.mapOnly
    width: Math.ceil(UI.paddingCommon + icon.width + textTemperature.width + UI.paddingCommon / 2)
    height: Math.ceil(UI.paddingCommon + UI.mapIconSizeHeight + Math.round(textLocation.height) + UI.paddingCommon)

    opacity: VCurrent.station ? 1 : 0

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

    CommonShadow {
        source: shadowSource
    }

    MaskedBlur {
        maskSource: rounded
        blurSource: contentPlaceholder
        sourceX: parent.x
        sourceY: parent.y
        color: UI.navBarColor
    }

    TextCore {
        id: textLocation
        padding: 0
        text: VCurrent.station ? VCurrent.station.display : ""
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        wrapMode: Text.WordWrap
        font.weight: Font.DemiBold
        font.pixelSize: UI.textCommon
        anchors {
            top: parent.top
            topMargin: UI.paddingCommon / 2
            left: parent.left
            leftMargin: UI.paddingCommon / 2
            right: parent.right
            rightMargin: UI.paddingCommon / 2
        }
    }


    Image {
        id: icon
        source: VCurrent.condition ? "icons/" + VCurrent.condition.icon + ".png" : ""
        width: UI.mapIconSize
        height: UI.mapIconSize
        anchors {
            bottom: parent.bottom
            bottomMargin: UI.paddingCommon / 2
            left: parent.left
            leftMargin: UI.paddingCommon / 2
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
            bottomMargin: UI.paddingCommon / 2 + (UI.mapIconSize - UI.mapIconSizeHeight)
            right: parent.right
            rightMargin: UI.paddingCommon / 2
        }
    }

    Behavior on opacity { PropertyAnimation { duration: UI.mapTimeChangeDuration } }
}
