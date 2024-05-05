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

import Vremenar 1.0

MouseArea {
    property bool active: false
    property bool shouldBeVisible: false

    id: loadingOverlay
    propagateComposedEvents: false
    hoverEnabled: true
    opacity: 0
    onWheel: {
        return false
    }

    onActiveChanged: {
        if (active) {
            timer.restart()
        } else {
            timer.stop()
            shouldBeVisible = false
        }
    }

    Rectangle {
        color: UI.navBarColor
        anchors {
            fill: parent
            topMargin: UI.safetyMarginTop
        }

        Spinner {
            id: indicator
            anchors.centerIn: parent
        }
    }

    Timer {
        id: timer
        interval: UI.loadingDelay; running: false; repeat: false
        onTriggered: {
            if (active) {
                shouldBeVisible = true
            }
        }
    }

    states: [
        State {
            when: shouldBeVisible
            PropertyChanges {
                target: loadingOverlay
                opacity: 1.0
            }
            PropertyChanges {
                target: indicator
                running: true
            }
        },
        State {
            when: !shouldBeVisible
            PropertyChanges {
                target: loadingOverlay
                opacity: 0.0
            }
            PropertyChanges {
                target: indicator
                running: false
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            property: "opacity"
            duration: UI.loadingTransitionDuration
        }
        onRunningChanged: {
            if (!running) {
                if (loadingOverlay.opacity == 0.0) {
                    loadingOverlay.visible = false
                }
            } else {
                if (loadingOverlay.active) {
                    loadingOverlay.visible = true
                }
            }
        }
    }
}
