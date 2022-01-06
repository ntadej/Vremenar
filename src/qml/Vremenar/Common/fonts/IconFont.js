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

.import "Ionicons/icons.js" as Ionicons
.import "Segoe/icons.js" as Segoe
.import "SF/icons.js" as SF

const hasSegoeFluentIcons = Qt.fontFamilies().includes("Segoe Fluent Icons")

const family =
{
    "Ionicons": "Ionicons",
    "Segoe": hasSegoeFluentIcons ? "Segoe Fluent Icons" : "Segoe MDL2 Assets",
    "SF": "SF Pro Display"
}

const icon =
{
    "Ionicons": Ionicons.icons,
    "Segoe": Segoe.icons,
    "SF": SF.icons
}

const hasWeights =
{
    "Ionicons": false,
    "Segoe": false,
    "SF": true
}

const weight =
{
    "SF": SF.weights
}
