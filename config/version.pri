#
# Vremenar
# Copyright (C) 2019 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

VERSION = $$cat($$top_srcdir/VERSION)
VERSION_BUILD = $$system(git -C \""$$top_srcdir"\" rev-list --count HEAD)

message("Building Vremenar version $$VERSION")
message("Build number: $$VERSION_BUILD")
