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

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

import "elements"

MapPageBase {
    title: VLocation.location ? VLocation.location : qsTr("Weather Map") + VL.R

    Map {
        LocationProvider {
            id: mapPlugin
        }

        id: map
        anchors.fill: parent

        plugin: mapPlugin
        zoomLevel: 8
        center: VLocation.position.isValid ? VLocation.position : VLocation.initial

        minimumZoomLevel: VWeather.minZoomLevel
        maximumZoomLevel: VWeather.maxZoomLevel
        maximumTilt: 0

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

        CurrentLocationIndicator {
        }
    }

    bottomSheetContents: MapControls {
        id: mapControls

        Binding { target: VMapLayersModel; property: "time"; value: mapControls.time }
    }
}
