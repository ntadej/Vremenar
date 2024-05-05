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
import QtLocation 5.12
import QtPositioning 5.12
import QtQml 2.14

import Vremenar 1.0

import "elements"

import "MapLayers.js" as MapLayers

MapPageBase {
    id: mapPage

    title: VMapLayersModel.title + VL.R

    Map {
        MappingProvider {
            id: mapPlugin
        }

        id: map
        objectName: "mapObject"
        anchors.fill: parent
        activeMapType: supportedMapTypes[VWeather.currentMapStyle]
        property int activeMapIndex: VWeather.currentMapStyle

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

        gesture.acceptedGestures: MapGestureArea.PinchGesture | MapGestureArea.PanGesture | MapGestureArea.FlickGesture
        minimumZoomLevel: VWeather.minZoomLevel
        maximumZoomLevel: VWeather.maxZoomLevel
        maximumTilt: 0

        Component.onCompleted: reinitPosition()

        property bool loading: false

        property var paramSource: null
        property var paramLayer: null
        property var paramPaint: null

        function addParameters(type, renderingType, urlPrevious: string, urlCurrent: string, urlNext: string) {
            MapLayers.addParameters(map, type, renderingType, urlPrevious, urlCurrent, urlNext)
        }

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

        Behavior on bearing {
            NumberAnimation {
                duration: UI.mapCoordinateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }

        function resetPosition() {
            VLocation.requestPositionUpdate();
            if (VLocation.position.isValid) {
                centerBehavior.enabled = true
                bearing = 0
            }
        }

        function reinitPosition() {
            center = VLocation.initial
            centerBehavior.enabled = true
        }
    }
}
