#
# Vremenar
# Copyright (C) 2019 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

# Define sources and headers
INCLUDEPATH += src

SOURCES += \
    src/main.cpp

# Define substitution files
ConfigFile.input = src/Config.h.in
ConfigFile.output = $$OUT_PWD/Config.h
QMAKE_SUBSTITUTES += ConfigFile

HEADERS += $$ConfigFile.output

OTHER_FILES += \
    src/Config.h.in

# Include subfolders
include(common/common.pri)
include(settings/settings.pri)
include(location/location.pri)
include(weather/weather.pri)
include(qml/qml.pri)
include(application/application.pri)

# Common resources
RESOURCES += \
    resources/Common/graphics.qrc

# Desktop common resources
macx|linux:!android {
    RESOURCES += \
        resources/Common/icons/icons.qrc
}
