#
# Vremenar
# Copyright (C) 2019 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

TARGET = Vremenar
CONFIG += qt

# Common configuration
include($$top_srcdir/config/version.pri)
include($$top_srcdir/config/build.pri)
include($$top_srcdir/config/platform.pri)

# Disabled for mobile for now
!ios {
    include($$top_srcdir/config/i18n.pri)
}

# Add QML imports
QML_IMPORT_PATH = src/qml

# Define sources and headers
INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/application/ApplicationWindow.cpp \
    src/application/BaseApplication.cpp \
    src/common/Common.cpp \
    src/common/ListModel.cpp \
    src/common/LocaleManager.cpp \
    src/common/LocalServer.cpp \
    src/common/Log.cpp \
    src/common/NetworkManager.cpp \
    src/common/NetworkManagerFactory.cpp \
    src/common/Resources.cpp \
    src/common/Output.cpp \
    src/common/api/APIHelpers.cpp \
    src/common/api/APILoader.cpp \
    src/common/api/APIRequestBase.cpp \
    src/location/LocationProvider.cpp \
    src/qml/Globals.cpp \
    src/qml/Qml.cpp \
    src/qml/UIManager.cpp \
    src/qml/UIColors.cpp \
    src/qml/UIDimensions.cpp \
    src/qml/UIEffects.cpp \
    src/qml/UITexts.cpp \
    src/settings/Settings.cpp \
    src/settings/SettingsDefaults.cpp \
    src/settings/SettingsKeys.cpp \
    src/weather/common/Weather.cpp \
    src/weather/common/WeatherProviderBase.cpp \
    src/weather/common/containers/MapLayer.cpp \
    src/weather/common/models/MapLayersModelBase.cpp \
    src/weather/common/models/MapLayersProxyModel.cpp \
    src/weather/arso/ARSOWeatherProvider.cpp \
    src/weather/arso/api/ARSOAPICommon.cpp \
    src/weather/arso/api/ARSOAPIMapLayers.cpp \
    src/weather/arso/api/ARSOAPIRequest.cpp \
    src/weather/arso/models/ARSOMapLayersModel.cpp

HEADERS += \
    src/application/ApplicationWindow.h \
    src/application/BaseApplication.h \
    src/common/Common.h \
    src/common/Helpers.h \
    src/common/ListItem.h \
    src/common/ListModel.h \
    src/common/LocaleManager.h \
    src/common/LocalServer.h \
    src/common/Log.h \
    src/common/NetworkManager.h \
    src/common/NetworkManagerFactory.h \
    src/common/Resources.h \
    src/common/Output.h \
    src/common/api/APIHelpers.h \
    src/common/api/APILoader.h \
    src/common/api/APIRequestBase.h \
    src/location/LocationProvider.h \
    src/qml/Globals.h \
    src/qml/Qml.h \
    src/qml/UIManager.h \
    src/settings/Settings.h \
    src/weather/common/Weather.h \
    src/weather/common/WeatherProviderBase.h \
    src/weather/common/containers/MapLayer.h \
    src/weather/common/models/MapLayersModelBase.h \
    src/weather/common/models/MapLayersProxyModel.h \
    src/weather/arso/ARSOWeatherProvider.h \
    src/weather/arso/api/ARSOAPICommon.h \
    src/weather/arso/api/ARSOAPIMapLayers.h \
    src/weather/arso/api/ARSOAPIRequest.h \
    src/weather/arso/models/ARSOMapLayersModel.h

# Desktop specific
macx {
    SOURCES += \
        src/application/DesktopApplication.cpp \
        src/application/SingleApplication.cpp \
        src/application/TrayIcon.cpp \
        src/settings/SettingsDialog.cpp

    HEADERS += \
        src/application/DesktopApplication.h \
        src/application/SingleApplication.h \
        src/application/TrayIcon.h \
        src/settings/SettingsDialog.h

    FORMS += \
        src/settings/SettingsDialog.ui
}

# Mobile specific
ios {
    SOURCES += \
        src/application/MobileApplication.cpp

    HEADERS += \
        src/application/MobileApplication.h
}

# macOS specific
macx {
    OBJECTIVE_SOURCES += \
        src/application/DesktopApplicationMacOS.mm \
        src/settings/SettingsDialogMacOS.mm
}

# Define resources
RESOURCES += \
    src/qml/qml.qrc \
    src/qml/Vremenar/vremenar.qrc \
    src/qml/Vremenar/Common/common.qrc \
    src/qml/Vremenar/Maps/maps.qrc \
    src/qml/Vremenar/Navigation/navigation.qrc \
    resources/icons/icons.qrc \
    resources/logo/desktop/logo.qrc

# Define QML files
OTHER_FILES += \
    src/qml/main.qml \
    src/qml/Vremenar/Common/qmldir \
    src/qml/Vremenar/Common/*.qml \
    src/qml/Vremenar/Common/components/*.qml \
    src/qml/Vremenar/Common/menus/*.qml \
    src/qml/Vremenar/Common/menus/+custommenu/*.qml \
    src/qml/Vremenar/Common/menus/+nativemenu/*.qml \
    src/qml/Vremenar/Common/text/*.qml \
    src/qml/Vremenar/Maps/qmldir \
    src/qml/Vremenar/Maps/*.qml \
    src/qml/Vremenar/Maps/models/*.qml \
    src/qml/Vremenar/Navigation/qmldir \
    src/qml/Vremenar/Navigation/*.qml \
    src/qml/Vremenar/Navigation/+ios/*.qml \
    src/qml/Vremenar/Navigation/elements/*.qml \
    src/qml/Vremenar/Weather/qmldir \
    src/qml/Vremenar/Weather/*.qml

# Define other files
OTHER_FILES += \
    src/Config.h.in

# Disabled on mobile for now
!ios {
    RESOURCES += \
        $$top_builddir/i18n.qrc
}
