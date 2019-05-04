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

import Vremenar 1.0
import Vremenar.Common 1.0
import Vremenar.Navigation 1.0

DialogBlur {
    id: dialog

    ListRadioView {
        title:  qsTr("Map type") + VL.R
        model: VMapInfoModel
        anchors.fill: parent

        onCurrentIndexChanged: {
            if (applicationWindow.ready) {
                VWeather.currentMapLayerChanged(currentIndex)
                dialog.accept()
            }
        }
    }
}
