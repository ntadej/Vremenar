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
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    property alias title: textTitle.text

    height: UI.navBarHeight + UI.safetyMarginTop

    BlurWithShadow {
        blurSource: contentPlaceholder
        color: UI.navBarColor
    }

    TapHandler {
        enabled: !(UI.isMobile || UI.isTV)
        onTapped: if (tapCount === 2) app.toggleMaximized()
        gesturePolicy: TapHandler.DragThreshold
    }

    DragHandler {
        enabled: !(UI.isMobile || UI.isTV)
        grabPermissions: TapHandler.CanTakeOverFromAnything
        onActiveChanged: if (active) { app.startSystemMove(); }
    }

    RowLayout {
        spacing: 0
        visible: UI.navBarHeight > 0
        anchors {
            fill: parent
            topMargin: UI.safetyMarginTop
            leftMargin: UI.safetyMarginLeft
            rightMargin: UI.safetyMarginRight
        }

        TextCommon {
            id: textTitle
            color: app.active ? UI.textColor : UI.textColorInactive
            font.weight: Font.DemiBold
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }
    }

    Image {
        enabled: UI.customWindowButtons
        visible: UI.customWindowButtons

        anchors {
            top: parent.top
            left: parent.left
            topMargin: (UI.windowButtonHeight - 24) / 2
            leftMargin: (UI.windowButtonHeight - 24) / 2
        }

        source: "qrc:/Vremenar/Logo/24x24/vremenar.png"
    }

    WindowControlButtons {
        enabled: UI.customWindowButtons
        visible: UI.customWindowButtons

        anchors {
            top: parent.top
            right: parent.right
        }
    }
}
