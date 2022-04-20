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

set_source_files_properties(logo/128x128/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 128x128/vremenar.png
)
set_source_files_properties(logo/128x128/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 128x128/vremenar@2x.png
)
set_source_files_properties(logo/16x16/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 16x16/vremenar.png
)
set_source_files_properties(logo/16x16/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 16x16/vremenar@2x.png
)
set_source_files_properties(logo/24x24/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 24x24/vremenar.png
)
set_source_files_properties(logo/24x24/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 24x24/vremenar@2x.png
)
set_source_files_properties(logo/256x256/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 256x256/vremenar.png
)
set_source_files_properties(logo/256x256/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 256x256/vremenar@2x.png
)
set_source_files_properties(logo/32x32/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 32x32/vremenar.png
)
set_source_files_properties(logo/32x32/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 32x32/vremenar@2x.png
)
set_source_files_properties(logo/48x48/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 48x48/vremenar.png
)
set_source_files_properties(logo/48x48/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 48x48/vremenar@2x.png
)
set_source_files_properties(logo/64x64/vremenar.png
    PROPERTIES QT_RESOURCE_ALIAS 64x64/vremenar@2x.png
)
set_source_files_properties(logo/64x64/vremenar@2x.png
    PROPERTIES QT_RESOURCE_ALIAS 64x64/vremenar.png
)

qt_add_resources(Vremenar logo
    PREFIX
        /Vremenar/Logo
    BASE
        resources/macOS
    FILES
        logo/128x128/vremenar.png
        logo/128x128/vremenar@2x.png
        logo/16x16/vremenar.png
        logo/16x16/vremenar@2x.png
        logo/24x24/vremenar.png
        logo/24x24/vremenar@2x.png
        logo/256x256/vremenar.png
        logo/256x256/vremenar@2x.png
        logo/32x32/vremenar.png
        logo/32x32/vremenar@2x.png
        logo/48x48/vremenar.png
        logo/48x48/vremenar@2x.png
        logo/64x64/vremenar.png
        logo/64x64/vremenar@2x.png
)
