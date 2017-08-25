/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/
import QtQuick 2.7
import QtLocation 5.6

import Vremenar 1.0

Plugin {
    // required: Plugin.AnyMappingFeatures
    preferred: ["mapboxgl", "mapbox"]

    PluginParameter {
        name: "mapbox.access_token"
        value: ""
    }
    PluginParameter {
        name: "mapboxgl.access_token"
        value: ""
    }
}