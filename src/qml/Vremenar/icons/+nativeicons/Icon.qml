/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtQuick.Window 2.12

import Vremenar 1.0

Item {
    property string icon: ""
    property string family: ""
    property int size
    property color color

    Image {
        anchors {
            alignWhenCentered: true
            centerIn: parent
        }

        source: icon != "" && family != "" ? `image://${family}/${IconFont.label[family][icon]}/${color}/${IconFont.weight[family][icon]}/${Screen.devicePixelRatio}` : ""
        sourceSize.width: size
        sourceSize.height: size
    }
}
