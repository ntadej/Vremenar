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

import Vremenar 1.0

BaseApplicationWindow {
    id: app

    property ApplicationWindow applicationWindow : app
    property bool ready: false

    flags: UI.theme === Vremenar.Common.LightTheme
           ? Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint | Qt.MacWindowToolBarButtonHint
           : Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint

    Component.onCompleted: {
        Vremenar.startCompleted(this)
        ready = true
    }
}
