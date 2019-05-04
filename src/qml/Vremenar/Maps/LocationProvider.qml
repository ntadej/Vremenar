/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.12
import QtLocation 5.12

import Vremenar 1.0

Plugin {
    preferred: ["mapboxgl"]

    PluginParameter {
        name: "mapboxgl.mapping.additional_style_urls"
        value: Globals.mapsStyle
    }
}
