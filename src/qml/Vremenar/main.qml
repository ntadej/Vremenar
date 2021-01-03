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
import Qt.labs.platform 1.0

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

MainWindow {
//    title: centralNavigationStack.currentItem.title ? centralNavigationStack.currentItem.title + " - " + Globals.name : Globals.name
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
        buttons: MessageDialog.Yes | MessageDialog.No
        text: VUpdates.message

        Connections {
            target: VUpdates
            function onUpdateAvailable() { updateDialog.open() }
        }

        onYesClicked: {
            Qt.openUrlExternally(VUpdates.url);
        }
    }
}
