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
    property int elements: (UI.showButtonMapType + (UI.showButtonMapPosition && VLocation.enabled) + UI.showButtonMapSettings)

    width: UI.mapElementSize
    height: elements * UI.mapElementSize + (elements - 1) * UI.lineThickness
    visible: !UI.mapOnly && (UI.showButtonMapType || (UI.showButtonMapPosition && VLocation.enabled))

    Rectangle {
        id: maskSource
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

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        IconButton {
            icon: "map"
            family: UI.iconTheme
            width: parent.width
            visible: UI.showButtonMapType

            onClicked: {
                if (!UI.isTV && (UI.deviceType === Common.Desktop || UI.deviceType === Common.DebuggingDevice)) {
                    if (typeof applicationWindow.mainMenu.mapMenu !== 'undefined') {
                        applicationWindow.mainMenu.mapMenu.open()
                    } else {
                        Vremenar.showMapsMenu()
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
            icon: "locate"
            family: UI.iconTheme
            width: parent.width
            visible: UI.showButtonMapPosition && VLocation.enabled

            onClicked: map.resetPosition()
        }

        CommonLine {
            width: parent.width
            visible: (UI.showButtonMapType || (UI.showButtonMapPosition && VLocation.enabled)) && UI.showButtonMapSettings
        }

        IconButton {
            icon: "settings"
            family: UI.iconTheme
            width: parent.width
            visible: UI.showButtonMapSettings

            onClicked: {
                if (UI.deviceType === Common.Desktop || UI.deviceType === Common.DebuggingDevice) {
                    if (typeof applicationWindow.mainMenu.settingsMenu !== 'undefined') {
                        applicationWindow.mainMenu.settingsMenu.open()
                    } else {
                        Vremenar.showSettingsMenu()
                    }
                } else {
                    VNotifications.nativeEnabledCheck()
                    mobileSettingsDialog.open()
                }
            }
        }
    }
}
