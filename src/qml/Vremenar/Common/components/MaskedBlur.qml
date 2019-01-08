/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.0
import QtGraphicalEffects 1.0

OpacityMask {
    property alias blurSource: blur.blurSource
    property alias color: blur.color
    property alias sourceX: blur.sourceX
    property alias sourceY: blur.sourceY

    anchors.fill: parent
    source: blur

    CommonBlur {
        id: blur
        visible: false
    }
}
