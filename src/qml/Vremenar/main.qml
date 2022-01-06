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
import Qt.labs.platform 1.0

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Fonts 1.0
import Vremenar.Navigation 1.0

MainWindow {
    id: app
    title: !UI.navBarTitleOnly ? centralNavigationStack.currentItem.title ? centralNavigationStack.currentItem.title + " - " + Globals.name : Globals.name : ''
    visible: true

    LoadFonts { }

    NavigationStack {
        id: centralNavigationStack
        anchors.fill: parent
    }

    Rectangle {
        id: debuggingRect
        visible: UI.debugging
        anchors.fill: parent
        anchors.topMargin: UI.safetyMarginTop
        anchors.bottomMargin: UI.safetyMarginBottom
        anchors.leftMargin: UI.safetyMarginLeft
        anchors.rightMargin: UI.safetyMarginRight
        color: "transparent"
        border.color: "red"
        border.width: 1

        // focus: true

        // Keys.onPressed: {
        //     UI.debugAction(event.key)
        //     event.accepted = true
        // }
    }

    MessageDialog {
        id: updateDialog
        buttons: UI.isMobile ? MessageDialog.Yes | MessageDialog.No : MessageDialog.Yes | MessageDialog.No
        text: qsTr("Update available") + VL.R
        informativeText: VUpdates.message

        Connections {
            target: VUpdates
            function onUpdateAvailable() { updateDialog.open() }
        }

        onYesClicked: {
            Qt.openUrlExternally(VUpdates.url);
        }
    }

    MessageDialog {
        id: errorDialog
        buttons: UI.isMobile ? MessageDialog.Retry | MessageDialog.Cancel : MessageDialog.Retry | MessageDialog.Cancel
        text: qsTr("Oops!") + VL.R
        informativeText: qsTr("An error has happened while loading weather data.") + VL.R

        Connections {
            target: VWeather
            function onLoadingError() {
                if (app.visible) {
                    errorDialog.open()
                }
            }
        }

        Connections {
            target: VWeather
            function onLoadingSuccess() {
                if (errorDialog.visible) {
                    errorDialog.close()
                }
            }
        }

        onRetryClicked: {
            VWeather.refresh()
        }
    }
}
