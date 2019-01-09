/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.1
import QtQuick.Layouts 1.1

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    width: UI.buttonMapSize
    height: 2 * UI.buttonMapSize + UI.lineThickness

    Rectangle {
        id: rounded
        radius: UI.bottomSheetRadius
        anchors.fill: parent
        visible: false
    }

    MaskedBlur {
        maskSource: rounded
        blurSource: contentPlaceholder
        sourceX: parent.x
        sourceY: parent.y
        color: UI.navBarColor
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        IconButton {
            icon: "ios-map"
            family: "Ionicons"
            width: parent.width

            onClicked: mapTypeDialog.open()
        }

        CommonLine {
            width: parent.width
        }

        IconButton {
            icon: "ios-locate"
            family: "Ionicons"
            width: parent.width
        }
    }
}
