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

Rectangle {
    default property alias contents: content.children

    property alias title: navBar.title
    property alias bottomSheetContents: bottomSheet.contents
    property bool retranslating: false

    Item {
        id: contentPlaceholder
        anchors.fill: parent

        Rectangle {
            id: content
            anchors {
                fill: parent
            }
        }
    }

    NavBar {
        id: navBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    BottomSheet {
        id: bottomSheet
        anchors {
           top: parent.bottom
           topMargin: -UI.bottomSheetBaseHeight
           horizontalCenter: parent.horizontalCenter
        }
    }

    Component.onCompleted: {

    }
}
