/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

import QtQuick 2.0
import QtQuick.Controls 2.0

import Vremenar.Maps 1.0

StackView {
    id: stack
    initialItem: pageMaps

    MapsPage {
        id: pageMaps
    }
}