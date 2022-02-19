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

include($$top_srcdir/config/version.pri)

linux:!android {
    TARGET = vremenar
} macos|ios {
    TARGET = Vremenar$$VERSION_SUFFIX
} else {
    TARGET = Vremenar
}

# Common configuration
include($$top_srcdir/config/build.pri)
include($$top_srcdir/config/platform.pri)

# Add sources
include($$top_srcdir/src/src.pri)
