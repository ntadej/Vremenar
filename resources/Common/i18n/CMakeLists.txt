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

find_package(Qt6 6.4 OPTIONAL_COMPONENTS LinguistTools)

if(COMMAND qt_add_translations)
    message(STATUS "Translations: ON")
    qt_add_translations(Vremenar
        TS_FILES
            en.ts
            de.ts
            sl.ts
    )
endif()
