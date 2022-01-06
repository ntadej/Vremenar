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

import Vremenar 1.0

import "../icons/IconFont.js" as IconFont

Core {
    property string icon: ""
    property string family: ""

    text: icon != "" && family != "" ? IconFont.icon[family][icon] : ""
    font.family: family != "" ? IconFont.family[family] : ""
    font.pixelSize: UI.iconSizeCommon
    font.weight: IconFont.hasWeights[family] && icon != "" && family != "" ? IconFont.weight[family][icon] : Font.Normal
    color: UI.textColor
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
}
