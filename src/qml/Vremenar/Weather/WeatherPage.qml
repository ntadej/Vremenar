/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

import Vremenar 1.0

Page {
    title: qsTr("Current Weather") + VL.R

    LinearGradient {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 1.0
                color: Colors.baseDark
            }
            GradientStop {
                position: 0.0
                color: Colors.baseLight
            }
        }
    }
}
