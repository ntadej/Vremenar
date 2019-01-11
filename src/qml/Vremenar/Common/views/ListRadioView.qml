/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.0
import QtQuick.Layouts 1.1

import Vremenar 1.0
import Vremenar.Common 1.0

ColumnLayout {
    property alias model: view.model
    property alias currentIndex: view.currentIndex
    property alias title: header.text

    spacing: 0

    TextHeader {
        id: header
        Layout.fillWidth: true
    }

    CommonLine {
        Layout.fillWidth: true
    }

    ListView {
        id: view

        Layout.fillWidth: true

        height: count * UI.rowHeight

        delegate: ListRadioDelegate {
            count: view.count
            checked: model.index === view.currentIndex
            text: model.display
            width: parent.width
            onClicked: view.currentIndex = model.index
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
