#
# Vremenar
# Copyright (C) 2023 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

SOURCES += \
    src/application/ApplicationWindow.cpp \
    src/application/BaseApplication.cpp \
    src/application/NotificationsManager.cpp \
    src/application/Updates.cpp \
    src/application/analytics/Analytics.cpp \
    src/application/analytics/AnalyticsEngine.cpp

HEADERS += \
    src/application/ApplicationWindow.h \
    src/application/BaseApplication.h \
    src/application/NotificationsManager.h \
    src/application/Services.h \
    src/application/Updates.h \
    src/application/analytics/Analytics.h \
    src/application/analytics/AnalyticsEngine.h

# Desktop specific
desktop {
    SOURCES += \
        src/application/DesktopApplication.cpp \
        src/application/SingleApplication.cpp \
        src/application/TrayIcon.cpp \
        src/application/dialogs/AboutDialog.cpp

    HEADERS += \
        src/application/DesktopApplication.h \
        src/application/SingleApplication.h \
        src/application/TrayIcon.h \
        src/application/dialogs/AboutDialog.h

    FORMS += \
        src/application/dialogs/AboutDialog.ui
}

# Mobile specific
mobile {
    SOURCES += \
        src/application/MobileApplication.cpp

    HEADERS += \
        src/application/MobileApplication.h
}

# macOS specific
macos {
    OBJECTIVE_SOURCES += \
        src/application/ApplicationDelegateMacOS.mm \
        src/application/DesktopApplicationMacOS.mm

    HEADERS += \
        src/application/ApplicationDelegateMacOS.h \
        src/application/ApplicationDelegateMacOSWrapper.h

    !store {
        OBJECTIVE_SOURCES += \
            src/application/SparkleHelperMacOS.mm

        HEADERS += \
            src/application/SparkleHelper.h
    }
}

# macOS/iOS specific
macos|ios {
    OBJECTIVE_SOURCES += \
        src/application/ImageProviderMacOSiOS.mm \
        src/application/NotificationsManagerMacOSiOS.mm \
        src/application/analytics/AnalyticsEngineMacOSiOS.mm

    HEADERS += \
        src/application/ImageProviderMacOSiOS.h \
        src/application/analytics/AnalyticsEngineMacOSiOS.h
}

# iOS specific
ios {
    OBJECTIVE_SOURCES += \
        src/application/ApplicationDelegateIOS.mm \
        src/application/MobileApplicationIOS.mm

    HEADERS += \
        src/application/ApplicationDelegateIOS.h
}

# Android specific
android {
    SOURCES += \
        src/application/AndroidJniInterface.cpp \
        src/application/NotificationsManagerAndroid.cpp \
        src/application/analytics/AnalyticsEngineAndroid.cpp

    HEADERS += \
        src/application/AndroidJniInterface.h \
        src/application/NotificationsManagerAndroid.h \
        src/application/analytics/AnalyticsEngineAndroid.h
}

# Linux/Windows specific
linux:!android|windows {
    SOURCES += \
        src/application/analytics/AnalyticsEngineCpp.cpp \
        src/application/analytics/Countly.cpp \
        src/application/analytics/CountlyEvent.cpp

    HEADERS += \
        src/application/analytics/AnalyticsEngineCpp.h \
        src/application/analytics/Countly.h
}

# Linux specific
linux:!android {
    SOURCES += \
        src/application/NotificationsManagerDummy.cpp
}

# Windows specific
win32 {
    SOURCES += \
        src/application/DesktopApplicationWin32.cpp \
        src/application/NativeEventFilterWin32.cpp \
        src/application/NotificationsManagerDummy.cpp

    HEADERS += \
        src/application/NativeEventFilterWin32.h

    !store {
        SOURCES += \
            src/application/SparkleHelperWin32.cpp

        HEADERS += \
            src/application/SparkleHelper.h
    }
}
