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

qt_add_resources(Vremenar graphics
    PREFIX
        /Vremenar/Logo
    FILES
        logo_tray.png
        logo_tray.svg
        logo_tray@2x.png
        logo_tray@3x.png
)

# LetsEncrypt
include(FetchContent)

FetchContent_Declare(LetsEncrypt_X1
    URL https://letsencrypt.org/certs/isrgrootx1.pem
    URL_HASH MD5=118ecd744d864b32ffdb48b2e29f1d7f
    DOWNLOAD_NO_EXTRACT TRUE
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/certificates"
)
FetchContent_MakeAvailable(LetsEncrypt_X1)

FetchContent_Declare(LetsEncrypt_X2
    URL https://letsencrypt.org/certs/isrg-root-x2.pem
    URL_HASH MD5=dccffc02a69e6dc186f6779e6bf0916e
    DOWNLOAD_NO_EXTRACT TRUE
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/certificates"
)
FetchContent_MakeAvailable(LetsEncrypt_X2)

qt_add_resources(Vremenar certificates
    PREFIX
        /
    FILES
        certificates/isrgrootx1.pem
        certificates/isrg-root-x2.pem
)
