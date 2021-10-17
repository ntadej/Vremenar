/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls

import Vremenar 1.0
import QtQuick.Controls.Universal 2.12

Controls.ApplicationWindow {
    id: appBase

    Universal.theme: UI.theme === Vremenar.Common.DarkTheme ? Universal.Dark : Universal.Light
    Universal.accent: UI.theme === Vremenar.Common.DarkTheme ? UI.colorPrimary : UI.colorPrimaryDark
}
