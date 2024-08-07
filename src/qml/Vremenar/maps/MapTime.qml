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
import QtQuick.Layouts 1.12

import Vremenar 1.0

Item {
    property alias textVisible: textTime.opacity

    visible: !UI.mapOnly
    width: Math.ceil(Math.max(textTime.width, textDay.text !== "" ? textDay.width : 0, Math.ceil(textRef.width / 10) * 10) + UI.paddingCommon)
    height: Math.ceil(textTime.height + (textDay.text !== "" ? textDay.height : 0) + UI.paddingCommon)

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

    TextCommon {
        id: textTime
        text: VMapLayersModel.daily ? VMapLayersModel.day : Qt.formatTime(new Date(VMapLayersModel.time))
        opacity: VMapLayersModel.time ? 1 : 0
        font.weight: Font.DemiBold

        anchors {
            top: parent.top
            topMargin: UI.paddingCommon / 2
            horizontalCenter: parent.horizontalCenter
        }
    }

    TextSmall {
        id: textDay
        padding: 0
        text: VMapLayersModel.daily ? "" : VMapLayersModel.day
        opacity: text !== "" ? 1 : 0
        color: VMapLayersModel.dayHighlighted ? UI.colorPrimary : UI.textColor

        anchors {
            bottom: parent.bottom
            bottomMargin: UI.paddingCommon / 2
            horizontalCenter: parent.horizontalCenter
        }

        Behavior on opacity { PropertyAnimation { duration: UI.mapTimeChangeDuration } }
    }

    TextCommon {
        id: textRef
        text: Qt.formatTime(new Date(0))
        visible: false
        font.weight: textTime.font.weight
    }

    Behavior on width { PropertyAnimation { duration: UI.mapTimeChangeDuration } }
    Behavior on height { PropertyAnimation { duration: UI.mapTimeChangeDuration } }
}
