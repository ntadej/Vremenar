/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
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
    id: layout

    property bool active: false
    property alias legend: mapLegend

    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
        bottomMargin: UI.radiusCommon
    }
    spacing: 0

    Shortcut {
        sequences: ["Space", "Media Play", "Media Pause", "Toggle Media Play/Pause"]
        onActivated: {
            buttonPlay.downAnimation()
            VMapLayersModel.play()
        }
    }
    Shortcut {
        sequences: ["Left", "Media Previous"]
        onActivated: {
            buttonPrevious.downAnimation()
            VMapLayersModel.previous()
        }
    }
    Shortcut {
        sequences: ["Right", "Media Next"]
        onActivated: {
            buttonNext.downAnimation()
            VMapLayersModel.next()
        }
    }
    Shortcut {
        sequences: ["Up"]
        onActivated: {
            VWeather.currentMapLayer -= 1
        }
    }
    Shortcut {
        sequences: ["Down"]
        onActivated: {
            VWeather.currentMapLayer += 1
        }
    }

    RowLayout {
        height: UI.mapElementSize
        Layout.maximumHeight: UI.mapElementSize

        IconButton {
            id: buttonInfo
            icon: mapPage.state === "sheet" ? UI.iconPrefix + "information-circle" : UI.iconPrefix + "information-circle-outline"
            family: UI.iconTheme
            width: UI.mapElementSize

            onClicked: mapPage.toggleSheetVisibility()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonPrevious
            icon: UI.iconPrefix + "rewind"
            family: UI.iconTheme
            width: UI.mapElementSize
            disabled: VMapLayersModel.minTimestamp === VMapLayersModel.time

            onClicked: VMapLayersModel.previous()
        }

        IconButton {
            id: buttonPlay
            icon: VMapLayersModel.animated ? UI.iconPrefix + "pause" : UI.iconPrefix + "play"
            family: UI.iconTheme
            width: UI.mapElementSize

            onClicked: VMapLayersModel.play()
        }

        IconButton {
            id: buttonNext
            icon: UI.iconPrefix + "fastforward"
            family: UI.iconTheme
            width: UI.mapElementSize
            disabled: VMapLayersModel.maxTimestamp === VMapLayersModel.time

            onClicked: VMapLayersModel.next()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonRefresh
            icon: UI.iconPrefix + "refresh"
            family: UI.iconTheme
            width: UI.mapElementSize

            RotationAnimator {
                id: buttonRefreshAnimator
                target: buttonRefresh
                from: 0
                to: 360
                duration: UI.hoverDuration
            }

            onClicked: {
                VWeather.refresh()
                buttonRefreshAnimator.running = true
            }
        }
    }

    MapLegendView {
        id: mapLegend
        model: VMapLegendModel
    }

    Item {
        Layout.preferredHeight: UI.radiusCommon
    }

    Item {
        Layout.fillHeight: true
    }

    TextSmall {
        id: labelUpdated
        text: qsTr("Last updated:") + " " + Qt.formatTime(new Date(VWeather.lastUpdateTime)) + VL.R
        Layout.maximumWidth: parent.width
        Layout.preferredHeight: UI.mapElementSize / 2
        opacity: 0
    }

    TextSmall {
        id: labelAbout
        text: qsTr("Weather data") + generateWeather() + "<br>"
              + qsTr("Maps") + generateMaps() + "<br>"
              + Globals.name + " " + Globals.version + " (" + Globals.build + ")"
              + generateAboutLinks()
              + VL.R
        wrapMode: Text.WordWrap
        linkColor: UI.textColorSpecialLink
        opacity: 0

        Layout.maximumWidth: parent.width

        onLinkActivated: {
            if (link == 'change_country') {
                countrySettingsDialog.open()
            } else {
                Qt.openUrlExternally(link)
            }
        }

        function generateWeather() {
            if (UI.deviceType === Common.Desktop || UI.deviceType === Common.AndroidTV) {
                return " " + VWeather.copyrightLink.html
            }

            return " " + VWeather.copyrightLink.html + " " + "<a href=\"change_country\">" + (qsTr("Change country") + VL.R) + "</a>"
        }

        function generateMaps() {
            let text = ""
            Globals.mapsCopyright.forEach(link => text += " " + link.html)
            return text
        }

        function generateAboutLinks() {
            let text = ""
            Globals.aboutLinks.forEach(link => text += " " + link.html)
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
            PropertyChanges { target: labelUpdated; opacity: 1 }
            PropertyChanges { target: labelAbout; opacity: 1 }
        }
    ]

    transitions: Transition {
        PropertyAnimation { property: "opacity"; duration: UI.hoverDuration }
    }
}
