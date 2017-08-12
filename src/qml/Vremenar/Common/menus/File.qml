/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.2
import QtQuick.Controls 1.2

Menu {
    title: qsTr("&File") + TNL.R

    MenuItem {
        text: Qt.platform.os === "osx" ? "E&xit" : qsTr("E&xit") + TNL.R
        shortcut: StandardKey.Quit
        onTriggered: Qt.quit()
    }

    MenuItem {
        text: Qt.platform.os === "osx" ? "Preferences" : qsTr(
                                             "Settings") + TNL.R
        onTriggered: VremenarSettings.show()
    }
}
