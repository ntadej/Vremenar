/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls

import Vremenar 1.0

Controls.ApplicationWindow {
    id: app
    property Controls.ApplicationWindow applicationWindow : app
    property bool ready: false

    onWidthChanged: UI.primaryWindowSizeChanged(width, height)
    onHeightChanged: UI.primaryWindowSizeChanged(width, height)

    Component.onCompleted: {
        Vremenar.startCompleted()
        ready = true
    }
}
