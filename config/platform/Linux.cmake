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
include(GNUInstallDirs)

# Extra installation rules
install(FILES
    "${CMAKE_SOURCE_DIR}/resources/Linux/vremenar.desktop"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
)

install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/16x16/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/16x16/apps"
)
install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/24x24/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/24x24/apps"
)
install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/32x32/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/32x32/apps"
)
install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/48x48/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/48x48/apps"
)
install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/64x64/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/64x64/apps"
)
install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/128x128/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/128x128/apps"
)
install(DIRECTORY
    "${CMAKE_SOURCE_DIR}/resources/Linux/logo/256x256/"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps"
)
