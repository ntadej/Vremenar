/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.7
import QtLocation 5.9
import QtPositioning 5.9

MapQuickItem {
    property var timestamp

    coordinate: QtPositioning.coordinate(model.maxLatitude, model.minLongitude)
    zoomLevel: 8
    sourceItem: Image {
        visible: model.timestamp === timestamp
        smooth: false
        fillMode: Image.Stretch
        source: model.url
        width: (model.maxLongitude - model.minLongitude) * map.ratioX
        height: (model.maxLatitude - model.minLatitude) * map.ratioY
    }

    Component.onCompleted: {
        if (!map.mapReady || (map.ratioX && map.ratioY))
            return

        var posMin = map.fromCoordinate(QtPositioning.coordinate(
                                            model.minLatitude,
                                            model.minLongitude), false)
        var posMax = map.fromCoordinate(QtPositioning.coordinate(
                                            model.maxLatitude,
                                            model.maxLongitude), false)

        map.ratioX = Math.abs(
                    (posMax.x - posMin.x) / (model.maxLongitude - model.minLongitude))
        map.ratioY = Math.abs(
                    (posMax.y - posMin.y) / (model.maxLatitude - model.minLatitude))
    }
}
