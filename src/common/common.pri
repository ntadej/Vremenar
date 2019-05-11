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

SOURCES += \
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
    src/common/containers/Hyperlink.cpp

HEADERS += \
    src/common/Common.h \
    src/common/Enums.h \
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
    src/common/containers/Hyperlink.h
