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
import QtGraphicalEffects 1.0

import Vremenar 1.0

Item {
    property alias blurSource: blurSource.sourceItem
    property alias color: blurRectangle.color
    property real sourceX
    property real sourceY
    property real sourceHeight: height

    anchors.fill: parent

    ShaderEffectSource {
        id: blurSource
        anchors.fill: parent
        sourceRect: Qt.rect(parent.sourceX, parent.sourceY, width, sourceHeight)
    }

    FastBlur {
        id: blur
        source: blurSource
        radius: UI.blurLevel
        anchors.fill: parent
    }

    Rectangle {
        id: blurRectangle
        color: "transparent"
        anchors.fill: parent
    }
}
