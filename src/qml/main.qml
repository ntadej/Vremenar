/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.7

import Vremenar.Navigation 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Vremenar"

    CentralSwipeView {
        id: centralSwipeView
        anchors.fill: parent
        indicator: centralPageIndicator
    }

    CentralPageIndicator {
        id: centralPageIndicator
        view: centralSwipeView
    }
}
