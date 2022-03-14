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
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Vremenar 1.0
import Vremenar.Common 1.0

import "elements"

DialogBlurFullWindow {
    id: dialog
    closePolicy: Popup.NoAutoClose

    SwipeView {
        id: view
        currentIndex: 0
        anchors.fill: parent
        interactive: false

        Item {
            id: pageWelcome

            Flickable {
                anchors.centerIn: parent
                width: Math.min(parent.width - 2 * Math.max(UI.safetyMarginLeft, UI.safetyMarginRight), 300)
                height: Math.min(parent.height - 2 * Math.max(UI.safetyMarginTop, UI.safetyMarginBottom), contentHeight)
                clip: true
                contentHeight: layoutWelcome.height

                ColumnLayout {
                    id: layoutWelcome
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }

                    Image {
                        source: "qrc:/Vremenar/Logo/128x128/vremenar.png"

                        Layout.alignment: Qt.AlignHCenter
                    }

                    TextCommon {
                        text: qsTr("Vremenar Setup") + VL.R
                        font.pixelSize: UI.textLarge
                        font.weight: Font.DemiBold
                        horizontalAlignment: Text.AlignHCenter

                        Layout.alignment: Qt.AlignHCenter
                    }

                    TextCommon {
                        text: qsTr("Personalise your experience when using this app.") + VL.R
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter

                        Layout.fillWidth: true
                    }

                    Item {
                        Layout.minimumHeight: UI.rowHeight
                        Layout.maximumHeight: UI.rowHeight
                    }

                    TextCommon {
                        text: qsTr("Confirm to continue...") + VL.R
                        visible: UI.isTV
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter

                        Layout.fillWidth: true
                    }

                    SimpleButton {
                        text: qsTr("Continue") + VL.R
                        visible: !UI.isTV

                        Layout.alignment: Qt.AlignHCenter

                        onClicked: action()
                        onConfirmed: action()

                        function action() {
                            view.currentIndex += 1
                        }
                    }

                    Shortcut {
                        sequences: ["Enter", "Return"]
                        enabled: dialog.opened && view.currentIndex === 0
                        onActivated: {
                            console.log("'Enter'/'Return' pressed")
                            view.currentIndex += 1
                        }
                    }
                }
            }
        }

        Item {
            id: pageSource

            Flickable {
                anchors.centerIn: parent
                width: Math.min(parent.width - 2 * Math.max(UI.safetyMarginLeft, UI.safetyMarginRight), 300)
                height: Math.min(parent.height - 2 * Math.max(UI.safetyMarginTop, UI.safetyMarginBottom), contentHeight)
                clip: true
                contentHeight: viewWelcomeSource ? viewWelcomeSource.height : 0

                SourceSelection {
                    id: viewWelcomeSource
                    shouldCloseDialog: false
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }

                    onSelected: {
                        if (view.currentIndex === view.count - 1) {
                            dialog.accept()
                        } else {
                            view.currentIndex += 1
                        }
                    }
                }
            }
        }

        Item {
            id: pageLocation

            Flickable {
                anchors.centerIn: parent
                width: Math.min(parent.width - 2 * Math.max(UI.safetyMarginLeft, UI.safetyMarginRight), 300)
                height: Math.min(parent.height - 2 * Math.max(UI.safetyMarginTop, UI.safetyMarginBottom), contentHeight)
                clip: true
                contentHeight: viewWelcomeLocation ? viewWelcomeLocation.height : 0

                LocationSettings {
                    id: viewWelcomeLocation
                    shouldCloseDialog: false
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }

                    onSelected: {
                        if (view.currentIndex === view.count - 1) {
                            dialog.accept()
                        } else {
                            view.currentIndex += 1
                        }
                    }
                }
            }
        }

        Item {
            id: pageNotifications

            Flickable {
                anchors.centerIn: parent
                width: Math.min(parent.width - 2 * Math.max(UI.safetyMarginLeft, UI.safetyMarginRight), 360)
                height: Math.min(parent.height - 2 * Math.max(UI.safetyMarginTop, UI.safetyMarginBottom), contentHeight)
                clip: true
                contentHeight: viewWelcomeNotifications? viewWelcomeNotifications.height : 0

                NotificationsSettings {
                    id: viewWelcomeNotifications
                    shouldCloseDialog: false
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                    }

                    onSelected: {
                        if (view.currentIndex === view.count - 1) {
                            dialog.accept()
                        } else {
                            view.currentIndex += 1
                        }
                    }
                }
            }
        }

        Component.onCompleted: {
            if (Settings.weatherSourceInitialChoice) {
                viewWelcomeSource.destroy()
                pageSource.destroy()
            }
            if (Settings.locationInitialChoice) {
                viewWelcomeLocation.destroy()
                pageLocation.destroy()
            }
            if (!VNotifications.nativeSupported() || Settings.notificationsInitialChoice) {
                viewWelcomeNotifications.destroy()
                pageNotifications.destroy()
            }
        }
    }

    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        delegate: PageIndicatorDelegate {
            currentIndex: indicator.currentIndex
        }

        anchors {
            bottom: view.bottom
            bottomMargin: UI.safetyMarginBottom + UI.mapElementOffset
            horizontalCenter: parent.horizontalCenter
        }
    }
}
