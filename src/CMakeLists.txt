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

configure_file(Config.h.in Config.h @ONLY)

qt_add_executable(Vremenar WIN32 MACOSX_BUNDLE
    main.cpp

    Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h

    $<$<PLATFORM_ID:Android>:application/AndroidJniInterface.cpp>
    $<$<PLATFORM_ID:Android>:application/AndroidJniInterface.h>
    $<$<PLATFORM_ID:iOS>:application/ApplicationDelegateIOS.h>
    $<$<PLATFORM_ID:iOS>:application/ApplicationDelegateIOS.mm>
    $<$<PLATFORM_ID:Darwin>:application/ApplicationDelegateMacOS.h>
    $<$<PLATFORM_ID:Darwin>:application/ApplicationDelegateMacOS.mm>
    $<$<PLATFORM_ID:Darwin>:application/ApplicationDelegateMacOSWrapper.h>
    application/ApplicationWindow.cpp
    application/ApplicationWindow.h
    application/BaseApplication.cpp
    application/BaseApplication.h
    $<$<NOT:$<BOOL:${MOBILE}>>:application/DesktopApplication.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/DesktopApplication.h>
    $<$<PLATFORM_ID:Darwin>:application/DesktopApplicationMacOS.mm>
    $<$<PLATFORM_ID:Windows>:application/DesktopApplicationWin32.cpp>
    $<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>:application/ImageProviderMacOSiOS.h>
    $<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>:application/ImageProviderMacOSiOS.mm>
    $<$<BOOL:${MOBILE}>:application/MobileApplication.cpp>
    $<$<BOOL:${MOBILE}>:application/MobileApplication.h>
    $<$<PLATFORM_ID:iOS>:application/MobileApplicationIOS.mm>
    $<$<PLATFORM_ID:Windows>:application/NativeEventFilterWin32.cpp>
    $<$<PLATFORM_ID:Windows>:application/NativeEventFilterWin32.h>
    application/NotificationsManager.cpp
    application/NotificationsManager.h
    $<$<PLATFORM_ID:Android>:application/NotificationsManagerAndroid.cpp>
    $<$<PLATFORM_ID:Android>:application/NotificationsManagerAndroid.h>
    $<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>:application/NotificationsManagerMacOSiOS.mm>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Windows>>:application/NotificationsManagerDummy.cpp>
    application/Services.h
    $<$<NOT:$<BOOL:${MOBILE}>>:application/SingleApplication.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/SingleApplication.h>
    $<$<AND:$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:Windows>>,$<NOT:$<BOOL:${STORE}>>>:application/SparkleHelper.h>
    $<$<AND:$<PLATFORM_ID:Darwin>,$<NOT:$<BOOL:${STORE}>>>:application/SparkleHelperMacOS.mm>
    $<$<AND:$<PLATFORM_ID:Windows>,$<NOT:$<BOOL:${STORE}>>>:application/SparkleHelperWin32.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/TrayIcon.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/TrayIcon.h>
    application/Updates.cpp
    application/Updates.h
    application/analytics/Analytics.cpp
    application/analytics/Analytics.h
    application/analytics/AnalyticsEngine.cpp
    application/analytics/AnalyticsEngine.h
    $<$<PLATFORM_ID:Android>:application/analytics/AnalyticsEngineAndroid.cpp>
    $<$<PLATFORM_ID:Android>:application/analytics/AnalyticsEngineAndroid.h>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Windows>>:application/analytics/AnalyticsEngineCpp.cpp>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Windows>>:application/analytics/AnalyticsEngineCpp.h>
    $<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>:application/analytics/AnalyticsEngineMacOSiOS.h>
    $<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>:application/analytics/AnalyticsEngineMacOSiOS.mm>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Windows>>:application/analytics/Countly.cpp>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Windows>>:application/analytics/Countly.h>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Windows>>:application/analytics/CountlyEvent.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/dialogs/AboutDialog.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/dialogs/AboutDialog.h>
    $<$<NOT:$<BOOL:${MOBILE}>>:application/dialogs/AboutDialog.ui>

    common/About.cpp
    common/About.h
    common/Enums.cpp
    common/Enums.h
    common/Helpers.h
    common/ListItem.cpp
    common/ListItem.h
    common/ListModel.cpp
    common/ListModel.h
    common/LocalServer.cpp
    common/LocalServer.h
    common/LocaleManager.cpp
    common/LocaleManager.h
    common/Log.cpp
    common/Log.h
    common/NetworkManager.cpp
    common/NetworkManager.h
    common/NetworkManagerFactory.cpp
    common/NetworkManagerFactory.h
    common/Output.cpp
    common/Output.h
    common/Resources.cpp
    common/Resources.h
    common/api/APIHelpers.cpp
    common/api/APIHelpers.h
    common/api/APILoader.cpp
    common/api/APILoader.h
    common/api/APIRequestBase.cpp
    common/api/APIRequestBase.h
    common/containers/Hyperlink.cpp
    common/containers/Hyperlink.h

    location/Location.cpp
    location/Location.h
    location/LocationProvider.cpp
    location/LocationProvider.h
    location/LocationProviderPlatform.h
    $<$<AND:$<PLATFORM_ID:Android>,$<BOOL:${POSITIONING}>>:location/LocationProviderAndroid.cpp>
    $<$<AND:$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>,$<BOOL:${POSITIONING}>>:location/LocationProviderMacOSiOS.h>
    $<$<AND:$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>,$<BOOL:${POSITIONING}>>:location/LocationProviderMacOSiOS.mm>

    maps/MapsCommon.cpp
    maps/MapsCommon.h
    maps/MapsManager.cpp
    maps/MapsManager.h

    qml/Globals.cpp
    qml/Globals.h
    qml/Qml.cpp
    qml/Qml.h
    qml/UIColors.cpp
    qml/UIDimensions.cpp
    qml/UIEffects.cpp
    qml/UIManager.cpp
    qml/UIManager.h
    $<$<PLATFORM_ID:Android>:qml/UIManagerAndroid.cpp>
    $<$<PLATFORM_ID:iOS>:qml/UIManagerIOS.mm>
    $<$<PLATFORM_ID:Darwin>:qml/UIManagerMacOS.mm>
    qml/UITexts.cpp

    settings/Settings.cpp
    settings/Settings.h
    settings/SettingsDefaults.cpp
    settings/SettingsKeys.cpp
    $<$<NOT:$<BOOL:${MOBILE}>>:settings/SettingsDialog.cpp>
    $<$<NOT:$<BOOL:${MOBILE}>>:settings/SettingsDialog.h>
    $<$<NOT:$<BOOL:${MOBILE}>>:settings/SettingsDialog.ui>
    $<$<PLATFORM_ID:Darwin>:settings/SettingsDialogMacOS.mm>

    weather/CurrentWeather.cpp
    weather/CurrentWeather.h
    weather/Sources.cpp
    weather/Sources.h
    weather/Weather.cpp
    weather/Weather.h
    weather/WeatherProvider.cpp
    weather/WeatherProvider.h
    weather/api/APIAlerts.cpp
    weather/api/APIAlerts.h
    weather/api/APIMapLayers.cpp
    weather/api/APIMapLayers.h
    weather/api/APIRequest.cpp
    weather/api/APIRequest.h
    weather/api/APIStations.cpp
    weather/api/APIStations.h
    weather/containers/MapInfo.cpp
    weather/containers/MapInfo.h
    weather/containers/MapLayer.cpp
    weather/containers/MapLayer.h
    weather/containers/MapLegendItem.cpp
    weather/containers/MapLegendItem.h
    weather/containers/StationInfo.cpp
    weather/containers/StationInfo.h
    weather/containers/WeatherAlert.cpp
    weather/containers/WeatherAlert.h
    weather/containers/WeatherCondition.cpp
    weather/containers/WeatherCondition.h
    weather/containers/WeatherInfo.cpp
    weather/containers/WeatherInfo.h
    weather/models/MapInfoModel.cpp
    weather/models/MapInfoModel.h
    weather/models/MapLayersModel.cpp
    weather/models/MapLayersModel.h
    weather/models/MapLayersProxyModel.cpp
    weather/models/MapLayersProxyModel.h
    weather/models/MapLegendModel.cpp
    weather/models/MapLegendModel.h
    weather/models/MapLegendProxyModel.cpp
    weather/models/MapLegendProxyModel.h
    weather/models/StationListModel.cpp
    weather/models/StationListModel.h
    weather/models/StationListProxyModel.cpp
    weather/models/StationListProxyModel.h
    weather/models/WeatherAlertModel.cpp
    weather/models/WeatherAlertModel.h
    weather/models/WeatherMapModel.cpp
    weather/models/WeatherMapModel.h
    weather/models/WeatherMapProxyModel.cpp
    weather/models/WeatherMapProxyModel.h

    $<$<PLATFORM_ID:iOS>:${APPLE_IOS_ASSET_CATALOGS}>
    $<$<PLATFORM_ID:iOS>:${APPLE_IOS_GOOGLESERVICE}>
    $<$<PLATFORM_ID:iOS>:${APPLE_IOS_STORYBOARD}>
    $<$<PLATFORM_ID:iOS>:${APPLE_IOS_TRANSLATIONS}>
)

add_subdirectory(qml/Vremenar)

target_link_libraries(Vremenar PRIVATE
    Qt::Core
    Qt::Gui
    $<$<OR:$<PLATFORM_ID:Darwin>,$<PLATFORM_ID:iOS>>:Qt::GuiPrivate>
    Qt::Location
    Qt::Positioning
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::Sql
    $<$<NOT:$<BOOL:${MOBILE}>>:Qt::Widgets>
)

set_target_properties(Vremenar
    PROPERTIES
    OUTPUT_NAME "${VREMENAR_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/Info.plist"
    QT_ANDROID_EXTRA_LIBS "${ANDROID_EXTRA_LIBS}"
    QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/Android/output"
)

if(IOS)
    set_target_properties(Vremenar
        PROPERTIES
        XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${CMAKE_BINARY_DIR}/Vremenar.entitlements"
        XCODE_EMBED_FRAMEWORKS "${APPLE_IOS_EMBED_FRAMEWORKS}"
    )
    set_source_files_properties(
        ${APPLE_IOS_ASSET_CATALOGS}
        ${APPLE_IOS_GOOGLESERVICE}
        ${APPLE_IOS_STORYBOARD}
        ${APPLE_IOS_TRANSLATIONS}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
endif()

target_link_libraries(Vremenar PRIVATE
    Vremenar-compiler-options
)

target_include_directories(Vremenar PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdparty/GSL/include
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_subdirectory(3rdparty)
    target_link_libraries(Vremenar PRIVATE
        QMacToolBar
        $<$<NOT:$<BOOL:${STORE}>>:${Sparkle}>
    )
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR IOS)
    target_link_libraries(Vremenar PRIVATE
        ${Countly}
    )
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR IOS)
    target_link_directories(Vremenar PRIVATE
        ${APPLE_SWIFT_SDK_PATH}
        ${APPLE_SWIFT_TOOLCHAIN_PATH}
    )
    target_link_libraries(Vremenar PRIVATE
        -ObjC
        ${nanopb}
        ${FBLPromises}
        ${GoogleDataTransport}
        ${GoogleUtilities}
        ${FirebaseCoreInternal}
        ${FirebaseCore}
        ${FirebaseInstallations}
        ${FirebaseMessaging}
    )
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_custom_command(TARGET Vremenar POST_BUILD
        COMMAND ${CMAKE_BINARY_DIR}/resign.sh
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Resigning..."
    )
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set_target_properties(Vremenar PROPERTIES OUTPUT_NAME vremenar)

    install(TARGETS Vremenar
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        FRAMEWORK DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endif()
