/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

PageIndicator {
    property SwipeView view

    interactive: true
    count: view.count
    currentIndex: view.currentIndex

    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
}
