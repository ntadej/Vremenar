#
# Vremenar
# Copyright (C) 2022 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

qt_add_qml_module(Vremenar
    URI Vremenar.Maps
    VERSION 1.0
    QML_FILES
        MapButtons.qml
        MapControls.qml
        MapCurrentAlerts.qml
        MapCurrentWeather.qml
        MapLayers.js
        MapPage.qml
        MapPageBase.qml
        MapTime.qml
        MappingProvider.qml
        elements/+materialstyle/MapSlider.qml
        elements/+universalstyle/MapSlider.qml
        elements/CurrentLocationIndicator.qml
        elements/MapLegendItem.qml
        elements/MapLegendView.qml
        elements/MapSettingsDialog.qml
        elements/MapSlider.qml
        elements/WeatherEntry.qml
    RESOURCE_PREFIX Vremenar/Maps
    RESOURCES
        qmldir
    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)
