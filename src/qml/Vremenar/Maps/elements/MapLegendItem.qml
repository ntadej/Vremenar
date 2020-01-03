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

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    property alias color: rectangle.color
    property alias value: text.text
    property bool placeholder: false
    property bool wide: false

    width: wide ? UI.mapLegendSizeWide : UI.mapLegendSize
    height: 2 * UI.mapLegendSize

    Rectangle {
        id: rectangle
        anchors.top: parent.top
        anchors.left: parent.left

        width: wide ? UI.mapLegendSizeWide : UI.mapLegendSize
        height: UI.mapLegendSize

        border.width: !placeholder && Qt.colorEqual(color, "transparent") ? 1 : 0
        border.color: UI.colorPrimary
    }

    TextCommon {
        id: text
        width: wide ? UI.mapLegendSizeWide : UI.mapLegendSize
        font.pixelSize: UI.textSmall
        horizontalAlignment: Text.AlignHCenter
        anchors.top: rectangle.bottom
        anchors.left: parent.left
        anchors.leftMargin: placeholder ? -width / 4 : -width / 2
    }
}
