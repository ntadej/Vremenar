/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.0
import QtQuick.Controls 1.2

Menu {
    title: Qt.platform.os === "osx" ? "&Help" : qsTr("&Help") + TNL.R
}
