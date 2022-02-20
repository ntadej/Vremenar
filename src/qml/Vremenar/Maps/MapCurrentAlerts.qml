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

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQml.Models 2.15

import Vremenar 1.0
import Vremenar.Common 1.0

Item {
    id: container

    property int contentWidth: content.width + UI.paddingSmall * 2

    visible: !UI.mapOnly
    height: Math.ceil(layout.height + UI.paddingSmall * 2)

    opacity: alerts.count ? 1 : 0

    function colorFromSeverity(severity) {
        if (severity === Weather.MinorSeverity) {
            return UI.alertMinorColor
        }
        if (severity === Weather.ModerateSeverity) {
            return UI.alertModerateColor
        }
        if (severity === Weather.SevereSeverity) {
            return UI.alertSevereColor
        }
        if (severity === Weather.ExtremeSeverity) {
            return UI.alertExtremeColor
        }
    }

    Rectangle {
        id: rounded
        radius: UI.radiusCommon
        anchors {
            fill: parent
            leftMargin: parent.width - contentWidth
        }
        visible: false
    }

    Rectangle {
        id: shadowSource
        color: UI.shadowColor
        radius: UI.radiusCommon
        anchors {
            fill: parent
            leftMargin: parent.width - contentWidth
        }
        visible: false
    }

    CommonShadow {
        source: shadowSource
        anchors {
            fill: parent
            leftMargin: parent.width - contentWidth
        }
    }

    MaskedBlur {
        maskSource: rounded
        blurSource: contentPlaceholder
        sourceX: parent.x + parent.width - contentWidth
        sourceY: parent.y
        color: UI.navBarColor
        anchors {
            fill: parent
            leftMargin: parent.width - contentWidth
        }
    }

    RowLayout {
        id: layout
        spacing: 0

        anchors {
            top: parent.top
            topMargin: UI.paddingSmall
            left: parent.left
            leftMargin: UI.paddingSmall
            right: parent.right
            rightMargin: UI.paddingSmall
        }

        Item {
            Layout.fillWidth: true
        }

        ColumnLayout {
            id: content
            spacing: UI.paddingSmall

            Repeater {
                id: alerts
                model: VCurrentAlerts

                Item {
                    Layout.preferredWidth: Math.max(event.implicitWidth, duration.implicitWidth) + icon.width + UI.paddingSmall / 2
                    Layout.maximumWidth: container.width - (UI.paddingSmall * 2)
                    Layout.minimumHeight: event.height + duration.height

                    Icon {
                        id: icon
                        icon: "alert"
                        family: UI.iconTheme
                        size: UI.iconSizeCommon
                        color: colorFromSeverity(model.severity)
                        anchors {
                            left: parent.left
                            top: parent.top
                        }
                        height: UI.iconAlertArea
                        width: height
                    }

                    TextCore {
                        id: event
                        text: model.display
                        font.pixelSize: UI.textCommon
                        wrapMode: Text.WordWrap
                        width: parent.width - (icon.width + UI.paddingSmall / 2)
                        anchors {
                            top: parent.top
                            left: parent.left
                            leftMargin: icon.width + UI.paddingSmall / 2
                        }
                    }

                    TextCore {
                        id: duration
                        text: model.duration
                        font.pixelSize: UI.textSmall
                        wrapMode: Text.WordWrap
                        width: parent.width - (icon.width + UI.paddingSmall / 2)
                        anchors {
                            top: event.bottom
                            left: parent.left
                            leftMargin: icon.width + UI.paddingSmall / 2
                        }
                    }
                }
            }
        }
    }

    Behavior on opacity { PropertyAnimation { duration: UI.mapTimeChangeDuration } }
}
