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
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Vremenar 1.0

import "elements"


ColumnLayout {
    id: layout

    property bool active: false
    property alias slider: mapSlider
    property alias sliderRow: mapSliderRow
    property alias legend: mapLegend
    property var navigation: UI.isTV ? Vremenar.Common.ControlsNavigation : Vremenar.Common.TypeNavigation
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
            buttonPlay.action()
        }
    }
    Shortcut {
        sequences: ["Media Rewind", "Media Previous"]
        onActivated: {
            console.log("'Media Previous/Rewind' pressed")
            buttonPrevious.action()
        }
    }
    Shortcut {
        sequences: ["Media Fast Forward", "Media Next"]
        onActivated: {
            console.log("'Media Next/Forward' pressed")
            buttonNext.action()
        }
    }
    Shortcut {
        sequences: ["Up"]
        onActivated: {
            console.log("'Up' pressed")
            if (navigation === Vremenar.Common.ControlsNavigation) {
                buttonRow.disableFocus()
            } else if (navigation === Vremenar.Common.TypeNavigation) {
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
            if (navigation === Vremenar.Common.ControlsNavigation) {
                buttonRow.enableFocus()
            } else if (navigation === Vremenar.Common.TypeNavigation) {
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
        enabled: navigation !== Vremenar.Common.ControlsNavigation
        onActivated: {
            console.log("'Left' pressed")
            if (navigation === Vremenar.Common.MoveNavigation) {
                map.pan(-delta, 0)
            }
        }
    }
    Shortcut {
        sequences: ["Right"]
        enabled: navigation !== Vremenar.Common.ControlsNavigation
        onActivated: {
            console.log("'Right' pressed")
            if (navigation === Vremenar.Common.MoveNavigation) {
                map.pan(delta, 0)
            }
        }
    }
    Shortcut {
        sequences: ["Enter", "Return"]
        enabled: !buttonRow.hasFocus()
        onActivated: {
            console.log("'Enter'/'Return' pressed")
            if (UI.isTV) {
                if (navigation === Vremenar.Common.ControlsNavigation) {
                    navigation = Vremenar.Common.TypeNavigation
                    UI.toast(qsTr("Map type can now be switched using up and down keys"))
                } else if (navigation === Vremenar.Common.TypeNavigation) {
                    navigation = Vremenar.Common.MoveNavigation
                    UI.toast(qsTr("Map can now be moved around with direction keys"))
                } else if (navigation === Vremenar.Common.MoveNavigation) {
                    navigation = Vremenar.Common.ZoomNavigation
                    UI.toast(qsTr("Map can now be zoomed using up and down keys"))
                } else if (navigation === Vremenar.Common.ZoomNavigation) {
                    navigation = Vremenar.Common.ControlsNavigation
                    UI.toast(qsTr("Map control buttons are now accessible"))
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
        sequences: UI.isTV ? ["Menu", "M"] : []
        onActivated: {
            console.log("'Menu' pressed")
            mapSettingsDialog.open()
        }
    }

    RowLayout {
        id: buttonRow
        height: UI.mapElementSize
        Layout.maximumHeight: UI.mapElementSize

        spacing: parent.width < 400 ? 0 : 5

        function enableFocus() {
            buttonPlay.forceActiveFocus()
        }

        function disableFocus() {
            buttonFirst.focus = false
            buttonPrevious.focus = false
            buttonPlay.focus = false
            buttonNext.focus = false
            buttonLast.focus = false
        }

        function hasFocus() {
            return buttonFirst.focus || buttonPrevious.focus || buttonPlay.focus || buttonNext.focus || buttonLast.focus
        }

        IconButton {
            id: buttonInfo
            visible: !UI.isTV
            icon: mapPage.state === "sheet" ? "information" : "information-outline"
            family: UI.iconTheme === "Material" && icon === "information-outline" ? "MaterialOutlined" : UI.iconTheme
            width: UI.mapElementSize

            onClicked: mapPage.toggleSheetVisibility()
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonFirst
            icon: "first"
            family: UI.iconTheme
            size: UI.iconSizeFirstLast
            width: UI.mapElementSize
            disabled: VMapLayersModel.minTimestamp === VMapLayersModel.time

            onClicked: action()
            onConfirmed: action()

            function action() {
                downAnimation()
                VMapLayersModel.first()
            }

            KeyNavigation.right: buttonPrevious.disabled ? buttonPlay : buttonPrevious
        }

        IconButton {
            id: buttonPrevious
            icon: "previous"
            family: UI.iconTheme
            size: UI.iconSizePrevNext
            width: UI.mapElementSize
            disabled: VMapLayersModel.minTimestamp === VMapLayersModel.time

            onClicked: action()
            onConfirmed: action()

            function action() {
                downAnimation()
                VMapLayersModel.previous()
            }

            KeyNavigation.left: buttonFirst.disabled ? null : buttonFirst
            KeyNavigation.right: buttonPlay
        }

        IconButton {
            id: buttonPlay
            icon: VMapLayersModel.animated ? "pause" : "play"
            family: UI.iconTheme
            width: UI.mapElementSize

            onClicked: action()
            onConfirmed: action()

            function action() {
                downAnimation()
                VMapLayersModel.play()
            }

            KeyNavigation.left: buttonPrevious.disabled ? null : buttonPrevious
            KeyNavigation.right: buttonNext.disabled ? null : buttonNext
        }

        IconButton {
            id: buttonNext
            icon: "next"
            family: UI.iconTheme
            size: UI.iconSizePrevNext
            width: UI.mapElementSize
            disabled: VMapLayersModel.maxTimestamp === VMapLayersModel.time

            onClicked: action()
            onConfirmed: action()

            function action() {
                downAnimation()
                VMapLayersModel.next()
            }

            KeyNavigation.left: buttonPlay
            KeyNavigation.right: buttonLast.disabled ? null : buttonLast
        }

        IconButton {
            id: buttonLast
            icon: "last"
            family: UI.iconTheme
            size: UI.iconSizeFirstLast
            width: UI.mapElementSize
            disabled: VMapLayersModel.maxTimestamp === VMapLayersModel.time

            onClicked: action()
            onConfirmed: action()

            function action() {
                downAnimation()
                VMapLayersModel.last()
            }

            KeyNavigation.left: buttonNext.disabled ? buttonPlay : buttonNext
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            id: buttonRefresh
            visible: !UI.isTV
            icon: "refresh"
            family: UI.iconTheme
            width: UI.mapElementSize
            disabled: VWeather.loading || VWeather.requesting

            RotationAnimator {
                id: buttonRefreshAnimator
                target: buttonRefresh
                from: 0
                to: 360
                duration: UI.hoverDuration
            }

            onClicked: {
                if (!VWeather.loading && !VWeather.requesting) {
                    VWeather.refresh()
                    buttonRefreshAnimator.running = true
                }
            }
        }
    }

    RowLayout {
        id: mapSliderRow
        Layout.minimumHeight: !UI.isTV ? mapSlider.implicitHeight + UI.mapElementOffset : 0

        Item {
            Layout.fillWidth: true
        }

        MapSlider {
            id: mapSlider
            enabled: !UI.isTV
            visible: !UI.isTV

            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: buttonRow.spacing * 4 + UI.mapElementSize * 5

            from: 0
            to: VMapLayersModel.count - 1
            value: VMapLayersModel.index
            onValueChanged: {
                if (VMapLayersModel.index !== value) {
                    VMapLayersModel.index = value
                }
            }

            stepSize: 1
            snapMode: Slider.SnapAlways
        }

        Item {
            Layout.fillWidth: true
        }
    }

    MapLegendView {
        id: mapLegend
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
        text: qsTr("Weather data") + " " + VWeather.copyrightLink.html + (UI.isTV ? " " : "<br>")
              + qsTr("Maps") + generateMaps() + (UI.isTV ? " " : "<br>")
              + (UI.isTV ? "" : Globals.name + " " + Globals.version + " (" + Globals.build + ")")
              + (UI.isTV || VUpdates.server === "" ? "" : ", " + qsTr("backend") + " " + VUpdates.server)
              + (UI.isTV ? "" : generateAboutLinks())
              + VL.R
        wrapMode: Text.WordWrap
        linkColor: UI.textColorSpecialLink
        opacity: 0

        Layout.maximumWidth: parent.width

        onLinkActivated: {
            Qt.openUrlExternally(link)
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
