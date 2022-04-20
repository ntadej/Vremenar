#
# Vremenar
# Copyright (C) 2022 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

qt_add_qml_module(Vremenar
    URI Vremenar.Navigation
    VERSION 1.0
    QML_FILES
        +mobile/MainWindow.qml
        LoadingOverlay.qml
        MainWindow.qml
        NavigationStack.qml
        Page.qml
        WelcomeDialog.qml
        elements/+mobile/WindowControlButtons.qml
        elements/BottomSheet.qml
        elements/DialogBlur.qml
        elements/DialogBlurFullWindow.qml
        elements/LocationSettings.qml
        elements/MobileSettingsDialog.qml
        elements/NavBar.qml
        elements/NotificationsSettings.qml
        elements/PageIndicatorDelegate.qml
        elements/SourceSelection.qml
        elements/WindowControlButtons.qml
    RESOURCE_PREFIX Vremenar/Navigation
    RESOURCES
        qmldir
    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)
