/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

ColumnLayout {
    property alias header: headerContent.visible
    property alias headerContents: headerContent.children

    property alias model: view.model
    property alias view: view
    property alias selectedIndex: view.selectedIndex
    property alias currentIndex: view.currentIndex
    property alias title: header.text
    property bool shouldHaveFocus: false

    property alias additionalView: view.additionalView

    signal confirmed()
    signal lostFocus()

    spacing: 0

    ColumnLayout {
        id: headerContent
        spacing: 0
    }

    TextHeader {
        id: header
        Layout.fillWidth: true
    }

    CommonLine {
        Layout.fillWidth: true
    }

    ListView {
        id: view
        focus: parent.shouldHaveFocus
        clip: true

        property int selectedIndex: 0
        property var additionalView: undefined
        currentIndex: -1

        Layout.fillWidth: true

        height: count * UI.rowHeight
        Layout.fillHeight: true
        Layout.minimumHeight: count * UI.rowHeight

        delegate: ListRadioDelegate {
            count: view.count
            text: model.display
            highlighted: ListView.isCurrentItem
            checked: model.index === view.selectedIndex
            translatable: model.translatable ? model.translatable : false
            width: view.width
            onHoveredChanged: {
                if (hovered) {
                    ListView.view.focus = true
                    ListView.view.currentIndex = model.index
                    if (typeof ListView.view.additionalView !== "undefined") {
                        ListView.view.additionalView.currentIndex = -1
                    }
                }
            }

            onClicked: select()
            Keys.onReturnPressed: select()
            Keys.onEnterPressed: select()

            function select() {
                if (ListView.view.selectedIndex === model.index) {
                    ListView.view.parent.confirmed()
                }
                ListView.view.selectedIndex = model.index
            }
        }

        onFocusChanged: {
            if (!focus) {
                currentIndex = -1
                lostFocus()
            }
        }
    }
}
