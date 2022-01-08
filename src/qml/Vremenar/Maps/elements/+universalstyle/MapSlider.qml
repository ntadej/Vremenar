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
import QtQuick.Controls 2.0
import QtQuick.Controls.Universal 2.0

import Vremenar 1.0

Slider {
    id: control
    hoverEnabled: !UI.isMobile

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 2
        width: control.availableWidth
        height: implicitHeight
        radius: height / 2

        x: control.leftPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        color: UI.theme === Vremenar.Common.DarkTheme ? control.Universal.baseMediumLowColor : UI.buttonColorHover

        Rectangle {
            width: control.position * parent.width
            height: parent.height
            radius: height / 2

            color: UI.buttonColor
        }
    }

    handle: Rectangle {
        implicitWidth: UI.mapSliderSize / 3
        implicitHeight: UI.mapSliderSize
        radius: 4

        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + (control.availableHeight - height) / 2

        color: control.pressed ? Qt.darker(UI.buttonColorHover, 1.1) :
               control.hovered ? UI.buttonColorHover : UI.buttonColor

        Behavior on color {
            ColorAnimation {
                duration: UI.hoverDuration
            }
        }
    }
}
