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

        property double ratioX: 0
        property double ratioY: 0

        id: map
        anchors.fill: parent

        activeMapType: supportedMapTypes[5]
        plugin: mapPlugin
        zoomLevel: 8
        center: VLocation.position.isValid ? VLocation.position : VLocation.initial

        minimumZoomLevel: VWeather.minZoomLevel
        maximumZoomLevel: VWeather.maxZoomLevel
        maximumTilt: 0

        MapItemView {
            id: mapItemView
            model: VMapLayersModel
            delegate: MapImageDelegate {
                timestamp: mapControls.slider.value
            }
        }

        CurrentLocationIndicator {
        }
    }

    bottomSheetContents: MapControls {
        id: mapControls
    }
}
