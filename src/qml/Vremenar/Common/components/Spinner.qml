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
import QtQuick.Controls 2.12

import Vremenar 1.0

BusyIndicator {
    id: control

    contentItem: Item {
        implicitWidth: 32
        implicitHeight: 32

        Image {
            id: image
            width: 32
            height: 32
            source: "../spinner.png"
            x: parent.width / 2 - 16
            y: parent.height / 2 - 16

            opacity: control.running ? 1 : 0

            Behavior on opacity { OpacityAnimator { duration: 150 } }

            RotationAnimator {
                target: image
                running: control.visible && control.running
                from: 0
                to: 360
                loops: Animation.Infinite
                duration: 1250
            }
        }
    }
}
