/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtLocation 5.9
import QtPositioning 5.9

import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

NavigationPage {
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
        center: VLocation.position

        CurrentLocationIndicator {
        }

        MapItemView {
            id: mapItemView
            model: VMapLayersModel
            delegate: mapLayerDelegate
        }

        Component {
            id: mapLayerDelegate

            MapImageDelegate {
                timestamp: mapSlider.value
            }
        }
    }

    bottomSheetContents: Slider {
        id: mapSlider
        from: VMapLayersModel.minTimestamp
        to: VMapLayersModel.maxTimestamp
        stepSize: VMapLayersModel.stepTimestamp
        value: VMapLayersModel.maxTimestamp
        snapMode: Slider.SnapAlways

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }
}
