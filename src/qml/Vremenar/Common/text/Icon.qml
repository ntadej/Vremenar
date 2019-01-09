/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.0

import Vremenar 1.0

import "../fonts/IconFont.js" as IconFont

Core {
    property string icon: ""
    text: icon != "" && font.family != "" ? IconFont.icon[font.family][icon] : ""
    color: UI.textColor
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
}
