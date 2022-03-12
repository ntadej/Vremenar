/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
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

DialogBlur {
    id: dialog
    implicitDialogWidth: 360
    implicitDialogHeight: layout.height

    property bool notificationsEnabled: true

    Flickable {
        anchors.fill: parent
        clip: true
        contentHeight: layout.height
        focus: dialog.opened

        KeyNavigation.down: viewNotificationsSettings.visible ? viewNotificationsSettings.view : viewLocationSettings.view

        ColumnLayout {
            id: layout
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            spacing: 0


            NotificationsSettings {
                id: viewNotificationsSettings
                visible: notificationsEnabled

                KeyNavigation.down: viewLocationSettings.view
            }

            ColumnLayout {
                id: layoutNotificationsDisabled
                visible: !viewNotificationsSettings.visible

                TextHeader {
                    text: qsTr("Weather Alert Notifications") + VL.R
                    Layout.fillWidth: true
                }

                CommonLine {
                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillWidth: true
                    Layout.minimumHeight: UI.rowHeight

                    TextCommon {
                        text: qsTr("Notifications are currently disabled by the operating system.") + VL.R
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                        anchors {
                            fill: parent
                            leftMargin: UI.paddingCommon
                            rightMargin: UI.paddingCommon
                        }
                    }
                }
            }

            Item {
                Layout.minimumHeight: UI.rowHeight / 4
                Layout.maximumHeight: UI.rowHeight / 4
            }

            LocationSettings {
                id: viewLocationSettings

                KeyNavigation.up: viewNotificationsSettings.visible ? viewNotificationsSettings.view : null
                KeyNavigation.down: viewSourceSettings.view
            }

            Item {
                Layout.minimumHeight: UI.rowHeight / 4
                Layout.maximumHeight: UI.rowHeight / 4
            }

            SourceSelection {
                id: viewSourceSettings

                KeyNavigation.up: viewLocationSettings.view
            }

            Item {
                Layout.minimumHeight: UI.radiusCommon
                Layout.maximumHeight: UI.radiusCommon
            }
        }
    }

    Connections {
        target: VNotifications
        function onNativeEnabledStatus(enabled) {
            notificationsEnabled = enabled
        }
    }
}
