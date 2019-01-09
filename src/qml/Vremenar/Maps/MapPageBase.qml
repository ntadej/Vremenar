/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.0

import Vremenar 1.0
import Vremenar.Navigation 1.0

Rectangle {
    default property alias contents: content.children

    property alias title: navBar.title
    property alias bottomSheetContents: bottomSheet.contents

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

    MapButtons {
        id: mapButtons
        anchors {
            top: parent.top
            right: parent.right
            topMargin: 2 * UI.navBarHeight
            rightMargin: UI.navBarHeight
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
}
