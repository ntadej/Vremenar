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

import QtLocation
import QtPositioning
import QtQml
import QtQuick
import Qt.labs.animation

import MapLibre 3.0

import Vremenar 1.0

import "elements"

import "MapLayers.js" as MapLayers

MapPageBase {
    id: mapPage

    title: VMapLayersModel.title + VL.R

    Component.onCompleted: map.resetPinchMinMax()

    Map {
        MappingProvider {
            id: mapPlugin
        }

        id: map
        objectName: "mapObject"
        anchors.fill: parent
        activeMapType: supportedMapTypes[VWeather.currentMapStyle]
        property int activeMapIndex: VWeather.currentMapStyle
        property bool pinchAdjustingZoom: false

        onActiveMapIndexChanged: function () {
            if (activeMapIndex === 1) {
                UI.theme = Vremenar.Common.LightTheme
            } else {
                UI.theme = Vremenar.Common.DarkTheme
            }
        }

        plugin: mapPlugin
        copyrightsVisible: false
        zoomLevel: Settings.startupMapEnabled ? Settings.startupMapZoomLevel : 8

        minimumZoomLevel: VWeather.minZoomLevel
        maximumZoomLevel: VWeather.maxZoomLevel
        maximumTilt: 0

        MapLibre.style: Style {
            id: mapStyle
            objectName: "mapStyleObject"

            function addParameters(type, renderingType, urlPrevious: string, urlCurrent: string, urlNext: string) {
                MapLayers.addParameters(mapStyle, type, renderingType, urlPrevious, urlCurrent, urlNext)
            }
        }

        Component.onCompleted: reinitPosition()

        property bool loading: false

        property var paramSource: null
        property var paramLayer: null
        property var paramPaint: null

        MapItemView {
            model: VWeatherMapModel
            delegate: WeatherEntry {
                icon: model.condition.icon
                title: model.display
                coordinate: model.station.coordinate
                temperature: model.condition.temperature
                temperatureLow: model.condition.temperatureLow
            }
        }

        CurrentLocationIndicator {
        }

        Binding { target: VWeatherMapModel; property: "zoomLevel"; value: map.zoomLevel }
        Binding { target: VWeatherMapModel; property: "visibleRegion"; value: map.visibleRegion }

        onCenterChanged: {
            if (!VLocation.validate(center)) {
                center = VLocation.validateAndCorrect(center)
            }
        }

        BoundaryRule on zoomLevel {
            id: zoomBoundaryRule
            minimum: map.minimumZoomLevel
            maximum: map.maximumZoomLevel
        }

        onZoomLevelChanged: {
            zoomBoundaryRule.returnToBounds();
            if (!pinchAdjustingZoom) resetPinchMinMax()
        }

        function resetPinchMinMax() {
            pinchHandler.persistentScale = 1
            pinchHandler.scaleAxis.minimum = Math.pow(2, map.minimumZoomLevel - map.zoomLevel + 1)
            pinchHandler.scaleAxis.maximum = Math.pow(2, map.maximumZoomLevel - map.zoomLevel - 1)
        }

        PinchHandler {
            id: pinchHandler
            target: null
            property geoCoordinate startCentroid
            onActiveChanged: if (active) {
                flickAnimation.stop()
                pinchHandler.startCentroid = map.toCoordinate(pinchHandler.centroid.position, false)
            } else {
                flickAnimation.restart(centroid.velocity)
                map.resetPinchMinMax()
            }
            onScaleChanged: (delta) => {
                if (!active) return

                map.pinchAdjustingZoom = true
                map.zoomLevel += Math.log2(delta)
                map.alignCoordinateToPoint(pinchHandler.startCentroid, pinchHandler.centroid.position)
                map.pinchAdjustingZoom = false
            }
            grabPermissions: PointerHandler.TakeOverForbidden
        }

        WheelHandler {
            id: wheelHandler
            // workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
            // Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
            // and we don't yet distinguish mice and trackpads on Wayland either
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            onWheel: (event) => {
                const loc = map.toCoordinate(wheelHandler.point.position)
                switch (event.modifiers) {
                    case Qt.NoModifier:
                        map.zoomLevel += event.angleDelta.y / 120
                        break
                }
                map.alignCoordinateToPoint(loc, wheelHandler.point.position)
            }
        }

         DragHandler {
            id: dragHandler
            signal flickStarted // for autotests only
            signal flickEnded
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
            onActiveChanged: if (active) {
                flickAnimation.stop()
            } else {
                flickAnimation.restart(centroid.velocity)
            }
        }

        property vector3d animDest
        onAnimDestChanged: if (flickAnimation.running) {
            const delta = Qt.vector2d(animDest.x - flickAnimation.animDestLast.x, animDest.y - flickAnimation.animDestLast.y)
            map.pan(-delta.x, -delta.y)
            flickAnimation.animDestLast = animDest
        }

        Vector3dAnimation on animDest {
            id: flickAnimation
            property vector3d animDestLast
            from: Qt.vector3d(0, 0, 0)
            duration: 500
            easing.type: Easing.OutQuad
            onStarted: dragHandler.flickStarted()
            onStopped: dragHandler.flickEnded()

            function restart(vel) {
                stop()
                map.animDest = Qt.vector3d(0, 0, 0)
                animDestLast = Qt.vector3d(0, 0, 0)
                to = Qt.vector3d(vel.x / duration * 100, vel.y / duration * 100, 0)
                start()
            }
        }

        Binding {
            target: map
            property: "center"
            when: centerBehavior.enabled && VLocation.position.isValid
            value: VLocation.position
            restoreMode: Binding.RestoreNone
        }

        Behavior on center {
            id: centerBehavior
            CoordinateAnimation {
                id: coordinateAnimation
                duration: UI.mapCoordinateChangeDuration
                easing.type: Easing.InOutQuad
                onRunningChanged: {
                    if (!running) {
                        map.center = VLocation.position
                        centerBehavior.enabled = false
                    }
                }
            }
            enabled: false
        }

        function resetPosition() {
            VLocation.requestPositionUpdate();
            if (VLocation.position.isValid) {
                centerBehavior.enabled = true
            }
        }

        function reinitPosition() {
            center = VLocation.initial
            centerBehavior.enabled = true
        }
    }
}
