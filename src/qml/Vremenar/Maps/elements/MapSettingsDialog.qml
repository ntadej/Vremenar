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
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

DialogBlur {
    id: dialog
    height: Math.min(parent.height, Math.max(400, view.view.count * UI.rowHeight + 175))

    ListRadioView {
        id: view
        title:  qsTr("Map type") + VL.R
        shouldHaveFocus: dialog.opened
        model: VMapInfoModel
        anchors.fill: parent

        selectedIndex: VWeather.currentMapLayer

        onSelectedIndexChanged: {
            if (applicationWindow.ready) {
                VWeather.currentMapLayerChanged(selectedIndex)
                dialog.accept()
            }
        }
        onConfirmed: {
            if (applicationWindow.ready) {
                dialog.accept()
            }
        }

        header: !UI.isTV
        headerContents: [
            TextHeader {
                text: qsTr("Map style") + VL.R
                Layout.fillWidth: true
            },

            CommonLine {
                Layout.fillWidth: true
            },

            Item {
                height: UI.rowHeight / 4
            },

            RowLayout {
                spacing: UI.rowHeight / 2
                Layout.fillWidth: true

                Item {
                    Layout.fillWidth: true
                }

                ImageButton {
                    width: UI.iconSizeLarge + 2 * UI.iconBorderThickness
                    active: VWeather.currentMapStyle === 0
                    image: "../../Common/satellite.png"
                    onClicked: {
                        VWeather.currentMapStyle = 0
                        dialog.accept()
                    }
                }

                ImageButton {
                    width: UI.iconSizeLarge + 2 * UI.iconBorderThickness
                    active: VWeather.currentMapStyle === 1
                    image: "../../Common/streets.png"
                    onClicked: {
                        VWeather.currentMapStyle = 1
                        dialog.accept()
                    }
                }

                Item {
                    Layout.fillWidth: true
                }
            },

            Item {
                height: UI.rowHeight / 4
            }
        ]
    }

    Binding { target: view; property: "selectedIndex"; value: VWeather.currentMapLayer }
}
