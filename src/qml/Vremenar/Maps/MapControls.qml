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
    property var navigation: Vremenar.Common.TypeNavigation
    property int delta: 48
    property real zoomDelta: 0.1

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
            console.log("'Media Previous/Rewind' pressed")
            buttonPlay.downAnimation()
            VMapLayersModel.play()
        }
    }
    Shortcut {
        sequences: ["Media Rewind", "Media Previous"]
        onActivated: {
            console.log("'Media Previous/Rewind' pressed")
            buttonPrevious.downAnimation()
            VMapLayersModel.previous()
        }
    }
    Shortcut {
        sequences: ["Media Fast Forward", "Media Next"]
        onActivated: {
            console.log("'Media Next/Forward' pressed")
            buttonNext.downAnimation()
            VMapLayersModel.next()
        }
    }
    Shortcut {
        sequences: ["Up"]
        onActivated: {
            console.log("'Up' pressed")
            if (navigation === Vremenar.Common.TypeNavigation) {
                VWeather.currentMapLayer -= 1
            } else if (navigation === Vremenar.Common.MoveNavigation) {
                map.pan(0, -delta)
            } else if (navigation === Vremenar.Common.ZoomNavigation) {
                map.zoomLevel += zoomDelta
            }
        }
    }
    Shortcut {
        sequences: ["Down"]
        onActivated: {
            console.log("'Down' pressed")
            if (navigation === Vremenar.Common.TypeNavigation) {
                VWeather.currentMapLayer += 1
            } else if (navigation === Vremenar.Common.MoveNavigation) {
                map.pan(0, delta)
            } else if (navigation === Vremenar.Common.ZoomNavigation) {
                map.zoomLevel -= zoomDelta
            }
        }
    }
    Shortcut {
        sequences: ["Left"]
        onActivated: {
            console.log("'Left' pressed")
            if (navigation === Vremenar.Common.MoveNavigation) {
                map.pan(-delta, 0)
            }
        }
    }
    Shortcut {
        sequences: ["Right"]
        onActivated: {
            console.log("'Right' pressed")
            if (navigation === Vremenar.Common.MoveNavigation) {
                map.pan(delta, 0)
            }
        }
    }
    Shortcut {
        sequences: ["Enter", "Return"]
        onActivated: {
            console.log("'Enter'/'Return' pressed")
            if (UI.isTV) {
                if (navigation === Vremenar.Common.TypeNavigation) {
                    navigation = Vremenar.Common.MoveNavigation
                    UI.toast(qsTr("Map can now be moved around with direction keys"))
                } else if (navigation === Vremenar.Common.MoveNavigation) {
                    navigation = Vremenar.Common.ZoomNavigation
                    UI.toast(qsTr("Map can now be zoomed using up and down keys"))
                } else if (navigation === Vremenar.Common.ZoomNavigation) {
                    navigation = Vremenar.Common.TypeNavigation
                    UI.toast(qsTr("Map type can now be switched using up and down keys"))
                }
            }
        }
    }
    Shortcut {
        sequences: ["Back"]
        onActivated: {
            console.log("'Back' pressed")
        }
    }
    Shortcut {
        sequences: ["Menu"]
        onActivated: {
            console.log("'Menu' pressed")
            mapSettingsDialog.open()
        }
    }

    RowLayout {
        height: UI.mapElementSize
        Layout.maximumHeight: UI.mapElementSize

        IconButton {
            id: buttonInfo
            visible: !UI.isTV
            icon: mapPage.state === "sheet" ? UI.iconPrefix + "information-circle" : UI.iconPrefix + "information-circle-outline"
            family: UI.iconTheme
            width: UI.mapElementSize

            onClicked: mapPage.toggleSheetVisibility()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonFirst
            icon: UI.iconPrefix + "skip-backward"
            family: UI.iconTheme
            size: UI.iconSizeSpecialControl
            width: UI.mapElementSize
            disabled: VMapLayersModel.minTimestamp === VMapLayersModel.time

            onClicked: VMapLayersModel.first()
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

        IconButton {
            id: buttonLast
            icon: UI.iconPrefix + "skip-forward"
            family: UI.iconTheme
            size: UI.iconSizeSpecialControl
            width: UI.mapElementSize
            disabled: VMapLayersModel.maxTimestamp === VMapLayersModel.time

            onClicked: VMapLayersModel.last()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonRefresh
            visible: !UI.isTV
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
        text: qsTr("Weather data") + generateWeather() + (UI.isTV ? " " : "<br>")
              + qsTr("Maps") + generateMaps() + (UI.isTV ? " " : "<br>")
              + (UI.isTV ? "" : Globals.name + " " + Globals.version + " (" + Globals.build + ")")
              + (UI.isTV ? "" : generateAboutLinks())
              + VL.R
        wrapMode: Text.WordWrap
        linkColor: UI.textColorSpecialLink
        opacity: 0

        Layout.maximumWidth: parent.width

        onLinkActivated: {
            if (link == 'change_country') {
                sourceSettingsDialog.open()
            } else {
                Qt.openUrlExternally(link)
            }
        }

        function generateWeather() {
            if (UI.deviceType === Common.Desktop || UI.isTV) {
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
