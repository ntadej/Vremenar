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

import QtQml 2.15
import QtQml.Models 2.15
import QtQuick 2.15
import Qt.labs.platform 1.1

import Vremenar 1.0

Item {
    property alias mapTypeMenu: mapTypeMenu
    property alias mapMenu: mapMenu
    property alias settingsMenu: settingsMenu

    ListModel {
        id: styleModel
        ListElement { display: qsTr("Satellite") }
        ListElement { display: qsTr("Streets (Light)") }
        ListElement { display: qsTr("Streets (Dark)") }
    }

    MenuBar {
        // File menu
        Menu {
            title: qsTr("&File") + VL.R

            MenuItem {
                text: Qt.platform.os === "osx" ? "E&xit" : qsTr("E&xit") + VL.R
                role: MenuItem.QuitRole
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }

            MenuItem {
                text: Qt.platform.os === "osx" ? "Preferences" : qsTr("Settings") + VL.R
                onTriggered: Vremenar.showSettingsDialog()
                role: MenuItem.PreferencesRole
            }
        }

        // Map Style
        Menu {
            id: mapStyleMenu

            title: qsTr("Map Style") + VL.R

            MenuItemGroup {
                id: mapStyleMenuGroup
                items: mapStyleMenu.items
                onTriggered: function(item) {
                    if (item.value === VWeather.currentMapStyle) {
                        item.checked = true
                    }
                }
            }

            Instantiator {
                model: styleModel

                MenuItem {
                    property int value: index
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapStyle === index
                    onTriggered: VWeather.currentMapStyle = index
                }

                onObjectAdded: function(index, object) {
                    mapStyleMenu.insertItem(index, object)
                }
                onObjectRemoved: function (object) {
                    mapStyleMenu.removeItem(object)
                }
            }
        }

        // Map Type
        Menu {
            id: mapTypeMenu

            title: qsTr("Map Type") + VL.R

            MenuItemGroup {
                id: mapTypeMenuGroup
                items: mapTypeMenu.items
                onTriggered: function(item) {
                    if (item.value === VWeather.currentMapLayer) {
                        item.checked = true
                    }
                }
            }

            Instantiator {
                model: VMapInfoModel

                MenuItem {
                    property int value: index
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapLayer === index
                    onTriggered: VWeather.currentMapLayerChanged(index)
                }

                onObjectAdded: function(index, object) {
                    mapTypeMenu.insertItem(index, object)
                }
                onObjectRemoved: function(object) {
                    mapTypeMenu.removeItem(object)
                }
            }
        }

        // Map Settings
        Menu {
            id: mapMenu
            visible: false

            MenuItemGroup {
                id: mapTypeGroup
                onTriggered: function(item) {
                    if (item.value === VWeather.currentMapLayer) {
                        item.checked = true
                    }
                }
            }

            MenuItemGroup {
                id: mapStyleGroup
                onTriggered: function(item) {
                    if (item.value === VWeather.currentMapStyle) {
                        item.checked = true
                    }
                }
            }

            Instantiator {
                model: VMapInfoModel

                MenuItem {
                    property int value: index
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapLayer === index
                    onTriggered: VWeather.currentMapLayerChanged(index)
                }

                onObjectAdded: function(index, object) {
                    mapMenu.insertItem(index, object)
                    mapTypeGroup.addItem(object)
                }
                onObjectRemoved: function(object) {
                    mapMenu.removeItem(object)
                    mapTypeGroup.removeItem(object)
                }
            }

            MenuSeparator {}

            Instantiator {
                model: styleModel

                MenuItem {
                    property int value: index
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapStyle === index
                    onTriggered: VWeather.currentMapStyle = index
                }

                onObjectAdded: function(index, object) {
                    mapMenu.insertItem(index + 1, object)
                    mapStyleGroup.addItem(object)
                }
                onObjectRemoved: function (object) {
                    mapMenu.removeItem(object)
                    mapStyleGroup.removeItem(object)
                }
            }
        }

        // Settings menu
        Menu {
            id: settingsMenu
            visible: false

            MenuItem {
                text: Qt.platform.os === "osx" ? qsTr("Preferences") + VL.R : qsTr("Settings") + VL.R
                onTriggered: Vremenar.showSettingsDialog()
                role: MenuItem.NoRole
            }

            MenuItem {
                text: qsTr("Check for updates") + VL.R
                onTriggered: VUpdates.checkForUpdates()
                visible: VUpdates.enabled
            }

            MenuItem {
                text: qsTr("About Vremenar") + VL.R
                onTriggered: Vremenar.showAboutDialog()
                role: MenuItem.NoRole
            }

            MenuItem {
                text: qsTr("Quit Vremenar") + VL.R
                onTriggered: Qt.quit()
                role: MenuItem.NoRole
                visible: Qt.platform.os === "osx" && !Settings.showInDock
            }
        }

        // Help menu
        Menu {
            title: qsTr("&Help") + VL.R

            MenuItem {
                text: qsTr("About Vremenar") + VL.R
                onTriggered: Vremenar.showAboutDialog()
                role: MenuItem.AboutRole
            }

            MenuItem {
                text: qsTr("&Check for updates") + VL.R
                onTriggered: VUpdates.checkForUpdates()
                visible: VUpdates.enabled
            }
        }
    }
}
