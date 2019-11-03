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
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    property alias title: textTitle.text

    height: UI.navBarHeight + UI.safetyMarginTop
    clip: true

    CommonBlur {
        blurSource: contentPlaceholder
        color: UI.navBarColor
    }

    MouseArea {
        property point clickPosition: Qt.point(0, 0)

        anchors.fill: parent

        onPressed: {
            clickPosition = Qt.point(mouse.x, mouse.y)
        }

        onPositionChanged: {
            applicationWindow.x += mouse.x - clickPosition.x
            applicationWindow.y += mouse.y - clickPosition.y
        }
    }

    RowLayout {
        spacing: 0
        anchors {
            fill: parent
            topMargin: UI.safetyMarginTop
            leftMargin: UI.safetyMarginLeft
            rightMargin: UI.safetyMarginRight
        }

        TextCommon {
            id: textTitle
            font.weight: Font.DemiBold
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }
    }
}
