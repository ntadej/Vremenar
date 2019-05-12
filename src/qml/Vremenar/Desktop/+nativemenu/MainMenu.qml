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
                onTriggered: Vremenar.showSettingsDialog()
            }
        }

        // Help menu
        Menu {
            title: Qt.platform.os === "osx" ? "&Help" : qsTr("&Help") + VL.R

            MenuItem {
                text: Qt.platform.os === "osx" ? "&About" : qsTr("&About") + VL.R
                onTriggered: Vremenar.showAboutDialog()
            }
        }
    }
}
