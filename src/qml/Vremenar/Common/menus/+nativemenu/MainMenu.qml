/*
* Vremenar
* Copyright (C) 20179 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.2
import Qt.labs.platform 1.1

Item {
    MenuBar {
        // File menu
        Menu {
            title: qsTr("&File") + VL.R

            MenuItem {
                text: Qt.platform.os === "osx" ? "E&xit" : qsTr("E&xit") + VL.R
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }

            MenuItem {
                text: Qt.platform.os === "osx" ? "Preferences" : qsTr(
                                                     "Settings") + VL.R
                onTriggered: VSettings.show()
            }
        }

        // Help menu
        Menu {
            title: Qt.platform.os === "osx" ? "&Help" : qsTr("&Help") + VL.R
        }
    }
}
