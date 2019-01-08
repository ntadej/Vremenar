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
    property alias title: textTitle.text

    height: UI.navBarHeight
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
            VApplicationWindow.x += mouse.x - clickPosition.x
            VApplicationWindow.y += mouse.y - clickPosition.y
        }
    }

    RowLayout {
        spacing: 0
        anchors.fill: parent

        TextCommon {
            id: textTitle
            font.weight: Font.DemiBold
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }
    }
}