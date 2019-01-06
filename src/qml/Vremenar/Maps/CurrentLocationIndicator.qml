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

import Vremenar 1.0

MapQuickItem {
    anchorPoint.x: rectangle.width / 2
    anchorPoint.y: rectangle.width / 2
    coordinate: VLocation.position

    sourceItem: Rectangle {
        id: rectangle
        width: 16
        height: width
        radius: width / 2
        color: UI.colorPrimary
        border.color: "white"
        border.width: 2
    }
}
