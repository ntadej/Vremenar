/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.12
import QtQuick.Controls 2.12

MenuBar {
    // File menu
    Menu {
        title: qsTr("&File") + VL.R

        MenuItem {
            text: qsTr("Settings") + VL.R
            onTriggered: VSettings.show()
        }

        MenuItem {
            text: qsTr("E&xit") + VL.R
            action: Action {
              shortcut: StandardKey.Quit
            }
            onTriggered: Qt.quit()
        }

    }

    // Help menu
    Menu {
        title: qsTr("&Help") + VL.R
    }
}
