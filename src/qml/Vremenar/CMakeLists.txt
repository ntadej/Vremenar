#
# Vremenar
# Copyright (C) 2024 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

qt_add_qml_module(
    Vremenar
    URI Vremenar
    VERSION 1.0
    QML_FILES
        main.qml

        application/BaseApplicationWindow.qml
        application/+materialstyle/BaseApplicationWindow.qml
        application/+universalstyle/BaseApplicationWindow.qml

        components/BlurWithShadow.qml
        components/CommonBlur.qml
        components/CommonLine.qml
        components/CommonMask.qml
        components/CommonShadow.qml
        components/IconButton.qml
        components/ImageButton.qml
        components/MaskedBlurWithShadow.qml
        components/ShadowSource.qml
        components/SimpleButton.qml
        components/Spinner.qml
        components/WindowButton.qml

        fonts/Loader.qml
        fonts/+materialstyle/Loader.qml

        icons/+nativeicons/Icon.qml
        icons/Icon.qml
        icons/IconFont.js
        icons/Ionicons.js
        icons/Material.js
        icons/SFSymbols.js
        icons/Segoe.js

        maps/MapButtons.qml
        maps/MapControls.qml
        maps/MapCurrentAlerts.qml
        maps/MapCurrentWeather.qml
        maps/MapLayers.js
        maps/MapPage.qml
        maps/MapPageBase.qml
        maps/MapTime.qml
        maps/MappingProvider.qml
        maps/elements/+materialstyle/MapSlider.qml
        maps/elements/+universalstyle/MapSlider.qml
        maps/elements/CurrentLocationIndicator.qml
        maps/elements/MapLegendItem.qml
        maps/elements/MapLegendView.qml
        maps/elements/MapSettingsDialog.qml
        maps/elements/MapSlider.qml
        maps/elements/WeatherEntry.qml

        text/Common.qml
        text/CommonShadow.qml
        text/Core.qml
        text/Header.qml
        text/Small.qml

        views/BottomSheet.qml
        views/DialogBlur.qml
        views/DialogBlurFullWindow.qml
        views/ListRadioDelegate.qml
        views/ListRadioView.qml
        views/LoadingOverlay.qml
        views/LocationSettings.qml
        views/MobileSettingsDialog.qml
        views/NavBar.qml
        views/NavigationStack.qml
        views/NotificationsSettings.qml
        views/Page.qml
        views/PageIndicatorDelegate.qml
        views/SourceSelection.qml
        views/WelcomeDialog.qml
        views/WindowControlButtons.qml
        views/+mobile/WindowControlButtons.qml

    RESOURCE_PREFIX Vremenar
    RESOURCES
        qmldir

    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)

add_subdirectory(fonts)

if(MOBILE)
    set_source_files_properties(application/MobileApplicationWindow.qml PROPERTIES
        QT_RESOURCE_ALIAS application/MainApplicationWindow.qml
    )

    qt_target_qml_sources(
        Vremenar
        QML_FILES
            application/MobileApplicationWindow.qml
        PREFIX Vremenar
    )
else()
    set_source_files_properties(application/DesktopApplicationWindow.qml PROPERTIES
        QT_RESOURCE_ALIAS application/MainApplicationWindow.qml
    )

    qt_target_qml_sources(
        Vremenar
        QML_FILES
            application/DesktopApplicationWindow.qml
            application/MainMenu.qml
            application/+custommenu/MainMenu.qml
            application/+nativemenu/MainMenu.qml
        PREFIX Vremenar
    )
endif()
