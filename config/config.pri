#
# Vremenar
# Copyright (C) 2017 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler).
DEFINES += QT_DEPRECATED_WARNINGS

# Enable logging
DEFINES += LOGGING=$$LOGGING

# Mapbox config
DEFINES += MAPBOX_API_TOKEN=\\\"$$MAPBOX_API_TOKEN\\\"

# Define mobile
ios {
    DEFINES += VREMENAR_MOBILE
}
