#
# Vremenar
# Copyright (C) 2020 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#
# SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
#

isEmpty(MAPS_ENDPOINT) {
    error("'MAPS_ENDPOINT' is not defined or empty!")
}

isEmpty(ARSO_API_ENDPOINT) {
    error("'ARSO_API_ENDPOINT' is not defined or empty!")
}

isEmpty(ARSO_API_RESOURCES) {
    error("'ARSO_API_RESOURCES' is not defined or empty!")
}

isEmpty(COUNTLY_APPKEY) {
    error("'COUNTLY_APPKEY' is not defined or empty!")
}

isEmpty(COUNTLY_ENDPOINT) {
    error("'COUNTLY_ENDPOINT' is not defined or empty!")
}

isEmpty(COUNTLY_SALT) {
    error("'COUNTLY_SALT' is not defined or empty!")
}
