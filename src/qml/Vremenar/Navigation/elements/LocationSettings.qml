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

import QtQuick 2.12

import Vremenar 1.0
import Vremenar.Common 1.0

ListRadioView {
    id: view
    title: qsTr("Weather for current location") + VL.R

    model: ListModel {
        id: locationModel

        ListElement {
            display: QT_TR_NOOP("Enable location")
            translatable: true
        }
        ListElement {
            display: QT_TR_NOOP("Disable location")
            translatable: true
        }
    }

    selectedIndex: Settings.startupLocationSetting

    onSelectedIndexChanged: action()
    onConfirmed: action()

    function action() {
        if (applicationWindow.ready) {
            Vremenar.locationSettingChanged(selectedIndex)

            if (shouldCloseDialog) {
                dialog.accept()
            }

            selected()
        }
    }
}
