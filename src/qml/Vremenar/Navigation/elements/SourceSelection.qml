/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
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
    title: qsTr("Weather source selection") + VL.R

    model: ListModel {
        id: countryModel

        ListElement {
            display: QT_TR_NOOP("Slovenia (ARSO)")
            translatable: true
        }
        ListElement {
            display: QT_TR_NOOP("Germany (DWD)")
            translatable: true
        }
    }

    selectedIndex: Settings.weatherSource

    onSelectedIndexChanged: action()
    onConfirmed: action()

    function action() {
        if (applicationWindow.ready) {
            Vremenar.weatherSourceChanged(selectedIndex)

            if (shouldCloseDialog) {
                dialog.accept()
            }

            selected()
        }
    }
}
