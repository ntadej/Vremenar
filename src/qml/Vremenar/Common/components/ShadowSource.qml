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

import Vremenar 1.0

Item {
    property alias radius: rectangle.radius

    anchors{
        margins: -2 * UI.shadowRadius
        fill: parent
    }
    visible: false

    Rectangle {
        id: rectangle
        color: UI.shadowColor
        radius: UI.radiusCommon
        anchors{
            margins: 2 * UI.shadowRadius
            fill: parent
        }
    }
}
