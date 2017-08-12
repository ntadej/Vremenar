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
import QtLocation 5.6

Page {
    title: qsTr("Maps")

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        zoomLevel: (maximumZoomLevel - minimumZoomLevel) / 2
        center {
            // The Qt Company in Oslo
            latitude: 59.9485
            longitude: 10.7686
        }
    }
}
