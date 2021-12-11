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

import QtQml 2.12
import QtQuick 2.12
import Qt.labs.platform 1.1

Item {
    property alias mapTypeMenu: mapTypeMenu

    ListModel {
        id: styleModel
        ListElement { display: "Satellite" }
        ListElement { display: "Streets (Light)" }
        ListElement { display: "Streets (Dark)" }
    }

    MenuBar {
        // File menu
        Menu {
            title: qsTr("&File") + VL.R

            MenuItem {
                text: Qt.platform.os === "osx" ? "E&xit" : qsTr("E&xit") + VL.R
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }

            MenuItem {
                text: Qt.platform.os === "osx" ? "Preferences" : qsTr("Settings") + VL.R
                onTriggered: Vremenar.showSettingsDialog()
            }
        }

        // Map Style
        Menu {
            id: mapStyleMenu

            title: qsTr("Map Style") + VL.R

            MenuItemGroup {
                id: mapStyleMenuGroup
                items: mapStyleMenu.items
            }

            Instantiator {
                model: styleModel

                MenuItem {
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapStyle === index
                    onTriggered: VWeather.currentMapStyle = index
                }

                onObjectAdded: mapStyleMenu.insertItem(index, object)
                onObjectRemoved: mapStyleMenu.removeItem(object)
            }
        }

        // Map Type
        Menu {
            id: mapTypeMenu

            title: qsTr("Map Type") + VL.R

            MenuItemGroup {
                id: mapTypeMenuGroup
                items: mapTypeMenu.items
            }

            Instantiator {
                model: VMapInfoModel

                MenuItem {
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapLayer === index
                    onTriggered: VWeather.currentMapLayerChanged(index)
                }

                onObjectAdded: mapTypeMenu.insertItem(index, object)
                onObjectRemoved: mapTypeMenu.removeItem(object)
            }
        }

        // Help menu
        Menu {
            title: Qt.platform.os === "osx" ? "&Help" : qsTr("&Help") + VL.R

            MenuItem {
                text: Qt.platform.os === "osx" ? "&About" : qsTr("&About") + VL.R
                onTriggered: Vremenar.showAboutDialog()
            }

            MenuItem {
                text: Qt.platform.os === "osx" ? "&Check for updates" : qsTr("&Check for updates") + VL.R
                onTriggered: VUpdates.checkForUpdates()
            }
        }
    }
}
