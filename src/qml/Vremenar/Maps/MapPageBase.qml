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

import Vremenar 1.0
import Vremenar.Navigation 1.0

import "elements"

Rectangle {
    default property alias contents: content.children

    property alias title: navBar.title
    property alias bottomSheetContents: bottomSheet.contents
    property bool dialogActive: false

    Item {
        id: contentPlaceholder
        anchors.fill: parent

        Rectangle {
            id: content
            anchors {
                fill: parent
            }
        }
    }

    MapButtons {
        id: mapButtons
        anchors {
            top: parent.top
            right: parent.right
            topMargin: 2 * UI.navBarHeight
            rightMargin: UI.navBarHeight
        }
    }

    NavBar {
        id: navBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    BottomSheet {
        id: bottomSheet
        anchors {
           top: parent.bottom
           topMargin: - (UI.bottomSheetBaseHeight + UI.safetyMarginBottom)
           horizontalCenter: parent.horizontalCenter
        }
    }

    MapSettingsDialog {
        id: mapSettingsDialog
        anchors.centerIn: parent

        onAboutToShow: dialogActive = true
        onAboutToHide: dialogActive = false
    }

    Shortcut {
        sequences: ["I"]
        onActivated: toggleSheetVisibility()
    }

    states: [
        State {
            name: "dialog"; when: dialogActive
            PropertyChanges { target: bottomSheet; anchors.topMargin: 0 }
            PropertyChanges { target: mapButtons; opacity: 0 }
        },
        State {
            name: "sheet"
            PropertyChanges {
                target: bottomSheet
                height: 5 * UI.bottomSheetBaseHeight + UI.radiusCommon + UI.safetyMarginBottom
                anchors.topMargin: -height + UI.radiusCommon
            }
        }
    ]

    transitions: Transition {
        PropertyAnimation { property: "anchors.topMargin"; duration: UI.hoverDuration }
        PropertyAnimation { property: "height"; duration: UI.hoverDuration }
        PropertyAnimation { property: "opacity"; duration: UI.hoverDuration }

    }

    function toggleSheetVisibility() {
        if (state != "sheet")
            state = "sheet"
        else
            state = ""
    }
}
