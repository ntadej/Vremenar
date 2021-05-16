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

VERSION = $$cat($$top_srcdir/config/VERSION)
!isEmpty(CUSTOM_BUILD) {
    VERSION_BUILD = $$CUSTOM_BUILD
} else {
    VERSION_BUILD = $$system(git -C \""$$top_srcdir"\" rev-list --count HEAD)
}

OTHER_FILES += $$top_srcdir/config/VERSION

message("Building Vremenar version $$VERSION")
message("Build number: $$VERSION_BUILD")
