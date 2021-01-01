/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

import QtQuick 2.12
import QtGraphicalEffects 1.0

import Vremenar 1.0

DropShadow {
    id: shadow
    anchors.fill: source
    radius: UI.shadowRadius
    samples: UI.shadowRadius * 2 + 1
    color: UI.shadowColor
}
