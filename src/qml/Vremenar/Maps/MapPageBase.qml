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
            topMargin: UI.navBarHeight + UI.mapElementOffset + UI.safetyMarginTop
            rightMargin: UI.mapElementOffset + UI.safetyMarginRight
        }
    }

    MapTime {
        id: mapTime
        anchors {
            top: parent.top
            left: parent.left
            topMargin: UI.navBarHeight + UI.mapElementOffset + UI.safetyMarginTop
            leftMargin: UI.mapElementOffset + UI.safetyMarginLeft
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
           topMargin: -height + UI.radiusCommon
           leftMargin: UI.safetyMarginLeft
           rightMargin: UI.safetyMarginRight
        }

        height: UI.bottomSheetBaseHeight + mapControls.legend.height + UI.radiusCommon + UI.safetyMarginBottom

        onFullWidthChanged: {
            anchors.left = undefined
            anchors.right = undefined
            anchors.horizontalCenter = undefined

            if (!fullWidth) {
                width = Math.min(parent.width - UI.safetyMarginLeft - UI.safetyMarginRight, UI.bottomSheetMaxWidth)
                anchors.horizontalCenter = parent.horizontalCenter
            } else {
                anchors.left = parent.left
                anchors.right = parent.right
            }
        }
    }

    MapSettingsDialog {
        id: mapSettingsDialog
        anchors.centerIn: parent

        onAboutToShow: dialogActive = true
        onAboutToHide: dialogActive = false
    }

    LoadingOverlay {
        id: loadingOverlay
        active: VWeather.loading || map.loading === true
        visible: false
        anchors.fill: parent
        anchors.topMargin: UI.navBarHeight
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
                height: mapControls.height + UI.radiusCommon + UI.safetyMarginBottom
            }
            PropertyChanges {
                target: mapControls
                active: true
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
