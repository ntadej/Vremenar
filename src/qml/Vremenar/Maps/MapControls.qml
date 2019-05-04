/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    anchors.fill: parent

    property alias time: mapSlider.value

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            height: UI.buttonMapSize

            IconButton {
                id: buttonPlay
                icon: mapSlider.running ? "ios-pause" : "ios-play"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: mapSlider.play()
            }

            Item {
                Layout.fillWidth: true
            }

            IconButton {
                id: buttonPrevious
                icon: "ios-rewind"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: mapSlider.previous()
            }

            TextCommon {
                text: Qt.formatTime(mapSlider.timestamp)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                Layout.fillHeight: true
                Layout.minimumWidth: 60
            }

            IconButton {
                id: buttonNext
                icon: "ios-fastforward"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: mapSlider.next()
            }

            Item {
                Layout.fillWidth: true
            }

            IconButton {
                id: buttonInfo
                icon: "ios-information-circle-outline"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: console.log("info")
            }
        }

        Slider {
            id: mapSlider
            from: VMapLayersModel.minTimestamp
            to: VMapLayersModel.maxTimestamp
            stepSize: VMapLayersModel.stepTimestamp
            value: VMapLayersModel.maxTimestamp
            snapMode: Slider.SnapAlways

            property alias running: mapSliderTimer.running
            property date timestamp: new Date()

            onValueChanged: {
                timestamp = new Date(value)
            }

            Timer {
                id: mapSliderTimer
                interval: 300; running: false; repeat: true
                onTriggered: mapSlider.next(true)
            }

            function play() {
                mapSliderTimer.running = !mapSliderTimer.running
            }

            function previous() {
                mapSliderTimer.running = false

                decrease()
            }

            function next(fromTimer = false) {
                if (!fromTimer) mapSliderTimer.running = false

                if (fromTimer && value == to) {
                    value = from
                } else {
                    increase()
                }
            }

            Shortcut {
                sequences: ["Space", "Media Play", "Media Pause", "Toggle Media Play/Pause"]
                onActivated: {
                    buttonPlay.downAnimation()
                    mapSlider.play()
                }
            }
            Shortcut {
                sequences: ["Left", "Media Previous"]
                onActivated: {
                    buttonPrevious.downAnimation()
                    mapSlider.previous()
                }
            }
            Shortcut {
                sequences: ["Right", "Media Next"]
                onActivated: {
                    buttonNext.downAnimation()
                    mapSlider.next()
                }
            }
        }
    }
}
