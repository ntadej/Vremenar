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
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    anchors.fill: parent

    property alias slider: mapSlider

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            height: UI.buttonMapSize

            IconButton {
                icon: "ios-play"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: console.log("play")
            }

            Item {
                Layout.fillWidth: true
            }

            IconButton {
                icon: "ios-rewind"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: console.log("back")
            }

            TextCommon {
                text: Qt.formatTime(mapSlider.timestamp)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                Layout.fillHeight: true
                Layout.minimumWidth: 60
            }

            IconButton {
                icon: "ios-fastforward"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: console.log("forward")
            }

            Item {
                Layout.fillWidth: true
            }

            IconButton {
                icon: "ios-information-circle-outline"
                family: "Ionicons"
                width: UI.buttonMapSize

                onClicked: console.log("info")
            }
        }

        Slider {
            id: mapSlider
            from: VMapLayersModel.minTimestamp
            to: VMapLayersModel.maxTimestamp
            stepSize: VMapLayersModel.stepTimestamp
            value: VMapLayersModel.maxTimestamp
            snapMode: Slider.SnapAlways

            property date timestamp: new Date()

            onValueChanged: {
                timestamp = new Date(value)
            }
        }
    }
}
