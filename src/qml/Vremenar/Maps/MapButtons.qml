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
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    width: UI.mapElementSize
    height: (UI.showButtonMapType + (UI.showButtonMapPosition && VLocation.enabled)) * UI.mapElementSize + UI.lineThickness
    visible: !UI.mapOnly && (UI.showButtonMapType || (UI.showButtonMapPosition && VLocation.enabled))

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

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        IconButton {
            icon: UI.iconPrefix + "map"
            family: UI.iconTheme
            width: parent.width
            visible: UI.showButtonMapType

            onClicked: {
                if (!UI.isTV && (UI.deviceType === Common.Desktop || UI.deviceType === Common.DebuggingDevice)) {
                    if (typeof applicationWindow.mainMenu.mapTypeMenu.open !== 'undefined') {
                        applicationWindow.mainMenu.mapTypeMenu.open()
                    } else {
                        applicationWindow.mainMenu.mapTypeMenu.popup()
                    }
                } else {
                    mapSettingsDialog.open()
                }
            }
        }

        CommonLine {
            width: parent.width
            visible: UI.showButtonMapType && (UI.showButtonMapPosition && VLocation.enabled)
        }

        IconButton {
            icon: UI.iconPrefix + "locate"
            family: UI.iconTheme
            width: parent.width
            visible: UI.showButtonMapPosition && VLocation.enabled

            onClicked: map.resetPosition()
        }
    }
}
