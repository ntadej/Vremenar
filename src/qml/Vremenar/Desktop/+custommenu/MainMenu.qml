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

import QtQml 2.12
import QtQuick 2.12
import QtQuick.Controls 2.12

MenuBar {
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

    // Map Type
    Menu {
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
            text: qsTr("&About") + VL.R
            onTriggered: Vremenar.showAboutDialog()
        }
    }
}
