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

import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12

MenuBar {
    property alias mapTypeMenu: mapTypeMenu

    // File menu
    Menu {
        title: qsTr("&File") + VL.R

        MenuItem {
            text: qsTr("Settings") + VL.R
            onTriggered: Vremenar.showSettingsDialog()
        }

        MenuItem {
            text: qsTr("E&xit") + VL.R
            action: Action {
              shortcut: StandardKey.Quit
            }
            onTriggered: Qt.quit()
        }

    }

    ListModel {
        id: styleModel
        ListElement { display: qsTr("Satellite") }
        ListElement { display: qsTr("Streets (Light)") }
        ListElement { display: qsTr("Streets (Dark)") }
    }

    // Map Style
    Menu {
        id: mapStyleMenu

        title: qsTr("Map Style") + VL.R

        Instantiator {
            model: styleModel

            MenuItem {
                text: model.display
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

        Instantiator {
            model: VMapInfoModel

            MenuItem {
                text: model.display
                onTriggered: VWeather.currentMapLayerChanged(index)
            }

            onObjectAdded: mapTypeMenu.insertItem(index, object)
            onObjectRemoved: mapTypeMenu.removeItem(object)
        }
    }

    // Help menu
    Menu {
        title: qsTr("&Help") + VL.R

        MenuItem {
            text: qsTr("About") + VL.R
            onTriggered: Vremenar.showAboutDialog()
        }

        // MenuItem {
        //    text: qsTr("&Check for updates") + VL.R
        //    onTriggered: VUpdates.checkForUpdates()
        // }
    }
}
