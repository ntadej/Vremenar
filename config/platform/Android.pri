#
# Vremenar
# Copyright (C) 2018 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

# Mapbox GL plugin requirement
QT += sql

DISTFILES += \
    $$top_srcdir/resources/Android/output/AndroidManifest.xml \
    $$top_srcdir/resources/Android/output/res/values/libs.xml \
    $$top_srcdir/resources/Android/output/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = \
        $$top_srcdir/resources/Android/output
