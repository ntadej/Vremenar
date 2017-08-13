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
    id: mapPlugin
    name: "here"

    PluginParameter {
        name: "here.app_id"
        value: ""
    }
    PluginParameter {
        name: "here.token"
        value: ""
    }
    PluginParameter {
        name: "here.mapping.highdpi_tiles"
        value: true
    }
}
