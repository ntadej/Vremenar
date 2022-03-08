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

import Vremenar 1.0
import Vremenar.Common 1.0

DialogBlur {
    id: dialog
    implicitDialogWidth: 400

    ListRadioView {
        id: view
        title: qsTr("Weather Alert Notifications") + VL.R
        shouldHaveFocus: dialog.opened
        anchors.fill: parent
        model: ListModel {
            id: notificationsModel

            ListElement {
                display: QT_TR_NOOP("Minor (yellow) alerts and higher")
                subtitle: QT_TR_NOOP("Levels 1-4")
                translatable: true
            }
            ListElement {
                display: QT_TR_NOOP("Moderate (orange) alerts and higher")
                subtitle: QT_TR_NOOP("Levels 2-4")
                translatable: true
            }
            ListElement {
                display: QT_TR_NOOP("Severe (red) alerts and higher")
                subtitle: QT_TR_NOOP("Levels 3-4")
                translatable: true
            }
            ListElement {
                display: QT_TR_NOOP("Extreme (purple) alerts only")
                subtitle: QT_TR_NOOP("Level 4")
                translatable: true
            }
            ListElement {
                display: QT_TR_NOOP("No weather alerts")
                subtitle: QT_TR_NOOP("Disabled")
                translatable: true
            }
        }

        selectedIndex: Settings.initialNotificationsSetting

        onSelectedIndexChanged: {
            dialog.accept()
            VNotifications.setNotificationsLevel(selectedIndex)
        }
        onConfirmed: {
            dialog.accept()
            VNotifications.setNotificationsLevel(selectedIndex)
        }

        KeyNavigation.down: viewSource.visible ? viewSource.view : null
        onLostFocus: {
            if (viewSource.visible) {
                viewSource.currentIndex = 0
                viewSource.view.focus = true
            }
        }

        SourceSelection {
            id: viewSource
            additionalView: view
            shouldHaveFocus: false

            KeyNavigation.up: view.view

            onLostFocus: {
                view.currentIndex = view.view.count - 1
                view.view.focus = true
            }
        }

        Connections {
            target: VNotifications
            function onNativeEnabledStatus(enabled) {
                // TODO: disable
                console.log(enabled)
            }
        }
    }
}
