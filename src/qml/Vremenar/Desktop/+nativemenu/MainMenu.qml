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

        // Map Settings
        Menu {
            id: mapMenu
            visible: false

            MenuItemGroup {
                id: mapTypeGroup
            }

            MenuItemGroup {
                id: mapStyleGroup
            }

            Instantiator {
                model: VMapInfoModel

                MenuItem {
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapLayer === index
                    onTriggered: VWeather.currentMapLayerChanged(index)
                }

                onObjectAdded: {
                    mapMenu.insertItem(index, object)
                    mapTypeGroup.addItem(object)
                }
                onObjectRemoved: {
                    mapMenu.removeItem(object)
                    mapTypeGroup.removeItem(object)
                }
            }

            MenuSeparator {}

            Instantiator {
                model: styleModel

                MenuItem {
                    text: model.display
                    checkable: true
                    checked: VWeather.currentMapStyle === index
                    onTriggered: VWeather.currentMapStyle = index
                }

                onObjectAdded: {
                    mapMenu.insertItem(index + 1, object)
                    mapStyleGroup.addItem(object)
                }
                onObjectRemoved: {
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
                text: qsTr("Settings") + VL.R
                onTriggered: Vremenar.showSettingsDialog()
                role: MenuItem.NoRole
            }

            MenuItem {
                text: qsTr("Check for updates") + VL.R
                onTriggered: VUpdates.checkForUpdates()
                visible: VUpdates.enabled
            }

            MenuItem {
                text: qsTr("About") + VL.R
                onTriggered: Vremenar.showAboutDialog()
                role: MenuItem.NoRole
            }
        }

        // Help menu
        Menu {
            title: qsTr("&Help") + VL.R

            MenuItem {
                text: qsTr("About") + VL.R
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
