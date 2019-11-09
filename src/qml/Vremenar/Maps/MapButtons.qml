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
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    width: UI.mapElementSize
    height: (UI.showButtonMapType +  UI.showButtonMapPosition) * UI.mapElementSize + UI.lineThickness
    visible: UI.showButtonMapType || UI.showButtonMapPosition

    Rectangle {
        id: rounded
        radius: UI.radiusCommon
        anchors.fill: parent
        visible: false
    }

    MaskedBlur {
        maskSource: rounded
        blurSource: contentPlaceholder
        sourceX: parent.x
        sourceY: parent.y
        color: UI.navBarColor
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        IconButton {
            icon: "ios-map"
            family: "Ionicons"
            width: parent.width
            visible: UI.showButtonMapType

            onClicked: mapSettingsDialog.open()
        }

        CommonLine {
            width: parent.width
            visible: UI.showButtonMapType && UI.showButtonMapPosition
        }

        IconButton {
            icon: "ios-locate"
            family: "Ionicons"
            width: parent.width
            visible: UI.showButtonMapPosition

            onClicked: map.resetPosition()
        }
    }
}
