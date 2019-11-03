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
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

import "elements"


ColumnLayout {
    property bool active: false
    property alias time: mapSlider.value

    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
        bottomMargin: UI.radiusCommon
    }
    spacing: 0

    RowLayout {
        height: UI.mapElementSize
        Layout.maximumHeight: UI.mapElementSize

        IconButton {
            id: buttonPlay
            icon: mapSlider.running ? "ios-pause" : "ios-play"
            family: "Ionicons"
            width: UI.mapElementSize

            onClicked: mapSlider.play()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonPrevious
            icon: "ios-rewind"
            family: "Ionicons"
            width: UI.mapElementSize

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
            width: UI.mapElementSize

            onClicked: mapSlider.next()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonInfo
            icon: mapPage.state === "sheet" ? "ios-information-circle" : "ios-information-circle-outline"
            family: "Ionicons"
            width: UI.mapElementSize

            onClicked: mapPage.toggleSheetVisibility()
        }
    }

    MapLegendView {
        id: mapLegend
        model: VMapLegendModel
        opacity: 0
    }

    Item {
        Layout.preferredHeight: UI.radiusCommon
    }

    Slider {
        id: mapSlider
        from: VMapLayersModel.minTimestamp
        to: VMapLayersModel.maxTimestamp
        stepSize: VMapLayersModel.stepTimestamp
        value: VMapLayersModel.maxTimestamp
        snapMode: Slider.SnapAlways
        visible: false
        Layout.maximumHeight: 0

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

    Item {
        Layout.fillHeight: true
    }

    TextSmall {
        id: labelUpdated
        text: qsTr("Last updated:") + " " + VWeather.lastUpdateTime + VL.R
        Layout.maximumWidth: parent.width
        Layout.preferredHeight: UI.mapElementSize / 2
        opacity: 0
    }

    TextSmall {
        id: labelAbout
        text: qsTr("Weather data") + generateWeather() + "<br>"
              + qsTr("Maps") + generateMaps() + "<br>"
              + Globals.name + " " + Globals.version + " (" + Globals.build + ")"
              + VL.R
        wrapMode: Text.WordWrap
        linkColor: UI.textColorSpecialLink
        opacity: 0

        Layout.maximumWidth: parent.width

        onLinkActivated: Qt.openUrlExternally(link)

        function generateWeather() {
            return " " + VWeather.copyrightLink.html
        }

        function generateMaps() {
            let text = ""
            Globals.mapsCopyright.forEach(link => text += " " + link.html)
            return text
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton // we don't want to eat clicks on the Text
            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
        }
    }

    states: [
        State {
            name: "active"; when: active
            PropertyChanges { target: mapLegend; opacity: 1 }
            PropertyChanges { target: labelUpdated; opacity: 1 }
            PropertyChanges { target: labelAbout; opacity: 1 }
        }
    ]

    transitions: Transition {
        PropertyAnimation { property: "opacity"; duration: UI.hoverDuration }
    }
}
