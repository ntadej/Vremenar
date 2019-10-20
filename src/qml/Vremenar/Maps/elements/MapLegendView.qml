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
import QtQuick.Layouts 1.12

import Vremenar 1.0

Item {
    property alias model: view.model

    Layout.fillWidth: true
    Layout.preferredHeight: UI.mapLegendSize

    ListView {
        id: view
        anchors.centerIn: parent
        interactive: false
        orientation: ListView.Horizontal

        width: count * UI.mapLegendSize
        height: UI.mapLegendSize

        delegate: MapLegendItem {
            color: model.color
            value: model.display
        }
    }
}
