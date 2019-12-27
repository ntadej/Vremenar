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
import QtLocation 5.12
import QtPositioning 5.12
import QtQml 2.14

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

import "elements"

MapPageBase {
    id: mapPage

    title: VLocation.location ? VLocation.location : qsTr("Weather Map") + VL.R

    Map {
        LocationProvider {
            id: mapPlugin
        }

        id: map
        objectName: "mapObject"
        anchors.fill: parent

        plugin: mapPlugin
        copyrightsVisible: false
        zoomLevel: Settings.startupMapEnabled ? Settings.startupMapZoomLevel : 8

        minimumZoomLevel: VWeather.minZoomLevel
        maximumZoomLevel: VWeather.maxZoomLevel
        maximumTilt: 0

        Component.onCompleted: {
            center = VLocation.initial
            centerBehavior.enabled = true
        }

        MapParameter {
            type: "source"

            property var name: "weatherSource"
            property var sourceType: "image"
            property var url: VMapLayersModel.url
            property var coordinates: VMapLayersModel.coordinates
        }

        MapParameter {
            type: "layer"

            property var name: "weather"
            property var layerType: "raster"
            property var source: "weatherSource"
            property var before: "settlement"
        }

        MapParameter {
            type: "paint"

            property var layer: "weather"
            property var rasterOpacity: 0.75
        }

        MapItemView {
             model: VForecastModel
             delegate: ForecastEntry {
                 icon: model.icon
                 title: model.display
                 coordinate: model.coordinate
             }
        }

        CurrentLocationIndicator {
        }

        Binding { target: VForecastModel; property: "zoomLevel"; value: map.zoomLevel }

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
    }

    bottomSheetContents: MapControls {
        id: mapControls
    }
}
