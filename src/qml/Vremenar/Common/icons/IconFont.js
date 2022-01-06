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

.import "Ionicons.js" as Ionicons
.import "Material.js" as Material
.import "Segoe.js" as Segoe
.import "SF.js" as SF

const hasSegoeFluentIcons = Qt.fontFamilies().includes("Segoe Fluent Icons")

const family =
{
    "Ionicons": "Ionicons",
    "Material": "Material Icons",
    "MaterialOutlined": "Material Icons Outlined",
    "Segoe": hasSegoeFluentIcons ? "Segoe Fluent Icons" : "Segoe MDL2 Assets",
    "SF": "SF Pro"
}

const icon =
{
    "Ionicons": Ionicons.icons,
    "Material": Material.icons,
    "MaterialOutlined": Material.icons,
    "Segoe": Segoe.icons,
    "SF": SF.icons
}

const hasWeights =
{
    "Ionicons": false,
    "Material": false,
    "MaterialOutlined": false,
    "Segoe": false,
    "SF": true
}

const weight =
{
    "SF": SF.weights
}
