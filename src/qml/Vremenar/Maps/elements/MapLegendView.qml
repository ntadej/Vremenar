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
    Layout.preferredHeight: VWeather.currentMapLayer !== 0 ? view.height : 0
    height: VWeather.currentMapLayer !== 0 ? view.height : 0
    opacity: VWeather.currentMapLayer !== 0 ? 1 : 0

    Behavior on opacity {
        animation: PropertyAnimation { duration: UI.hoverDuration }
        enabled: !dialogActive
    }
    Behavior on height {
        animation: PropertyAnimation { duration: UI.hoverDuration }
        enabled: !dialogActive
    }

    ListView {
        id: view
        anchors {
            top: parent.top
            centerIn: parent
        }

        interactive: false
        orientation: ListView.Horizontal

        width: count * UI.mapLegendSize
        height: 2 * UI.mapLegendSize

        delegate: MapLegendItem {
            color: model.color
            value: model.display
        }
    }
}
