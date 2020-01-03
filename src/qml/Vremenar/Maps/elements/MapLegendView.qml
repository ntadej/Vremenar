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
    property bool hasLegend: VWeather.currentMapLayerHasLegend

    Layout.fillWidth: view.computedWidth > parent.width
    Layout.alignment: Qt.AlignHCenter
    Layout.preferredHeight: hasLegend ? 2 * UI.mapLegendSize : 0
    Layout.preferredWidth: view.computedWidth
    height: hasLegend ? 2 * UI.mapLegendSize : 0
    opacity: hasLegend ? 1 : 0

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
        anchors.fill: parent
        orientation: ListView.Horizontal

        property bool wide: count < 8
        property int computedWidth: count * (wide ? UI.mapLegendSizeWide : UI.mapLegendSize)

        delegate: MapLegendItem {
            color: model.color
            value: model.display
            placeholder: model.placeholder
            wide: view.wide
        }
    }
}
