#
# Vremenar
# Copyright (C) 2021 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

# Countly
INCLUDEPATH += $$top_srcdir/3rdparty/Countly/Windows
LIBS += -L$$top_srcdir/3rdparty/Countly/Windows -lcountly
