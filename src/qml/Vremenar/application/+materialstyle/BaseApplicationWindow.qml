/*
* Vremenar
* Copyright (C) 2025 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import Vremenar 1.0

ApplicationWindow {
    id: appBase

    Material.theme: UI.theme === Vremenar.Common.DarkTheme ? Material.Dark : Material.Light
    Material.accent: UI.buttonColor
    Material.primary: UI.buttonColorHover

    // for now we handle padding manually
    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0
}
