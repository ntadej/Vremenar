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
    URI Vremenar.Common
    VERSION 1.0
    QML_FILES
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
        icons/+nativeicons/Icon.qml
        icons/Icon.qml
        icons/IconFont.js
        icons/Ionicons.js
        icons/Material.js
        icons/SFSymbols.js
        icons/Segoe.js
        text/Common.qml
        text/CommonShadow.qml
        text/Core.qml
        text/Header.qml
        text/Small.qml
        views/ListRadioDelegate.qml
        views/ListRadioView.qml
    RESOURCE_PREFIX Vremenar/Common
    RESOURCES
        qmldir
    NO_GENERATE_QMLDIR
    NO_GENERATE_QMLTYPES
    NO_RESOURCE_TARGET_PATH
)
