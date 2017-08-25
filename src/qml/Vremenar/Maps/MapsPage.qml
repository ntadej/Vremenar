/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtLocation 5.9
import QtPositioning 5.9

Page {
    title: qsTr("Maps") + VL.R

    LocationProvider {
        id: mapPlugin
    }

    Map {
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
            model: VMapLayersModel
            delegate: mapLayerDelegate
        }

        MapImageDelegate {
            id: mapLayerDelegate
        }
    }
}
