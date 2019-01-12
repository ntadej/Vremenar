/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.12

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

ApplicationWindow {
//    title: centralNavigationStack.currentItem.title ? centralNavigationStack.currentItem.title + " - " + Globals.name : Globals.name
    visible: true

    LoadFonts { }

    NavigationStack {
        id: centralNavigationStack
        anchors.fill: parent
    }
}
