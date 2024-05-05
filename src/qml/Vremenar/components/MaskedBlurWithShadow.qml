/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12

Item {
    property alias blurSource: blur.blurSource
    property alias maskSource: mask.maskSource
    property alias shadowSource: shadow.source
    property alias color: blur.blurColor
    property alias sourceX: blur.sourceX
    property alias sourceY: blur.sourceY
    property alias sourceHeight: blur.sourceHeight

    anchors.fill: parent

    CommonShadow {
        id: shadow
    }

    CommonMask {
        id: mask
        source: blur
        anchors.fill: parent

        CommonBlur {
            id: blur
            visible: false
        }
    }
}
