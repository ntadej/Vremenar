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
import QtLocation 5.12
import QtPositioning 5.12
import QtQml 2.14

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

import "elements"

MapPageBase {
    id: mapPage

    title: VMapLayersModel.title + VL.R

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

        property bool loading: false
        property string currentUrl: "data:image/jpeg;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNkYAAAAAYAAjCB0C8AAAAASUVORK5CYII"

        property var paramSource: null
        property var paramLayer: null
        property var paramPaint: null

        function addParameters(type, url: string) {
            if (paramPaint) {
                map.removeMapParameter(paramPaint)
                paramPaint.destroy()
                paramPaint = null
            }
            if (paramLayer) {
                map.removeMapParameter(paramLayer)
                paramLayer.destroy()
                paramLayer = null
            }
            if (paramSource) {
                map.removeMapParameter(paramSource)
                paramSource.destroy()
                paramSource = null
            }

            if (type === Weather.IconsRendering) {
                return
            }

            console.log(VMapLayersModel.coordinates)

            if (type === Weather.TilesRendering) {
                url += '&bbox={bbox-epsg-3857}'
                paramSource = Qt.createQmlObject(`import QtLocation 5.15; DynamicParameter {type: "source"; objectName: "weatherSourceObj"; property var name: "weatherSource"; property var sourceType: "raster"; property var tiles: ["${url}"]; property var tileSize: 512;}`,
                                                 map,
                                                 "sourceParam")
            } else {
                paramSource = Qt.createQmlObject(`import QtLocation 5.15; DynamicParameter {type: "source"; objectName: "weatherSourceObj"; property var name: "weatherSource"; property var sourceType: "image"; property var url: map.currentUrl; property var coordinates: VMapLayersModel.coordinates;}`,
                                                 map,
                                                 "sourceParam")
            }

            paramLayer = Qt.createQmlObject('import QtLocation 5.15; DynamicParameter {type: "layer"; objectName: "weatherLayerObj"; property var name: "weatherLayer"; property var layerType: "raster"; property var source: "weatherSource"; property var before: "settlement";}',
                                            map,
                                            "layerParam")

            paramPaint = Qt.createQmlObject('import QtLocation 5.15; DynamicParameter {type: "paint";  objectName: "weatherPaintObj"; property var layer: "weatherLayer"; property var rasterOpacity: 0.75;}',
                                            map,
                                            "paintParam")

            map.addMapParameter(paramSource)
            map.addMapParameter(paramLayer)
            map.addMapParameter(paramPaint)
        }

        MapItemView {
             model: VWeatherMapModel
             delegate: WeatherEntry {
                 icon: model.icon
                 title: model.display
                 coordinate: model.coordinate
                 temperature: model.temperature
                 temperatureLow: model.temperatureLow
             }
        }

        CurrentLocationIndicator {
        }

        Binding { target: VWeatherMapModel; property: "zoomLevel"; value: map.zoomLevel }
        Binding { target: map; property: "currentUrl"; value: VMapLayersModel.image }

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
