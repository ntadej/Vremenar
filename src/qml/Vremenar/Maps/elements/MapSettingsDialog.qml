/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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
    height: Math.min(parent.height, view.view.count * UI.rowHeight + (viewSource.visible ? (viewSource.view.count + 1) * UI.rowHeight + 70 : 175))

    ListRadioView {
        id: view
        title:  qsTr("Map type") + VL.R
        shouldHaveFocus: dialog.opened
        model: VMapInfoModel
        anchors.fill: parent

        selectedIndex: VWeather.currentMapLayer
        additionalView: viewSource

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
                    id: buttonSatellite
                    width: UI.iconSizeLarge + 2 * UI.iconBorderThickness
                    active: VWeather.currentMapStyle === 0
                    image: "../../Common/satellite.png"
                    onClicked: select()
                    onConfirmed: select()
                    KeyNavigation.right: buttonStreetsLight
                    KeyNavigation.down: view.view

                    onFocusChanged: {
                        if (!focus && !buttonStreetsLight.focus && !buttonStreetsDark.focus) {
                            view.currentIndex = 0
                            view.view.focus = true
                        }
                    }

                    function select() {
                        VWeather.currentMapStyle = 0
                        dialog.accept()
                    }
                }

                ImageButton {
                    id: buttonStreetsLight
                    width: UI.iconSizeLarge + 2 * UI.iconBorderThickness
                    active: VWeather.currentMapStyle === 1
                    image: "../../Common/streets-light.png"
                    onClicked: select()
                    onConfirmed: select()
                    KeyNavigation.left: buttonSatellite
                    KeyNavigation.right: buttonStreetsDark
                    KeyNavigation.down: view.view

                    onFocusChanged: {
                        if (!focus && !buttonSatellite.focus && !buttonStreetsDark.focus) {
                            view.currentIndex = 0
                            view.view.focus = true
                        }
                    }

                    function select() {
                        VWeather.currentMapStyle = 1
                        dialog.accept()
                    }
                }

                ImageButton {
                    id: buttonStreetsDark
                    width: UI.iconSizeLarge + 2 * UI.iconBorderThickness
                    active: VWeather.currentMapStyle === 2
                    image: "../../Common/streets-dark.png"
                    onClicked: select()
                    onConfirmed: select()
                    KeyNavigation.left: buttonStreetsLight
                    KeyNavigation.down: view.view

                    onFocusChanged: {
                        if (!focus && !buttonSatellite.focus && !buttonStreetsLight.focus) {
                            view.currentIndex = 0
                            view.view.focus = true
                        }
                    }

                    function select() {
                        VWeather.currentMapStyle = 2
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

        KeyNavigation.up: header ? buttonSatellite : null
        KeyNavigation.down: viewSource.visible ? viewSource.view : null
        onLostFocus: {
            if (viewSource.visible && !buttonSatellite.focus) {
                viewSource.currentIndex = 0
                viewSource.view.focus = true
            }
        }

        SourceSelection {
            id: viewSource
            visible: UI.isTV
            additionalView: view
            shouldHaveFocus: false

            KeyNavigation.up: view.view

            onLostFocus: {
                view.currentIndex = view.view.count - 1
                view.view.focus = true
            }
        }
    }

    Binding { target: view; property: "selectedIndex"; value: VWeather.currentMapLayer }
}
