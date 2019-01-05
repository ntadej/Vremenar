#
# Vremenar
# Copyright (C) 2017 Tadej Novak <tadej@tano.si>
#
# This application is bi-licensed under the GNU General Public License
# Version 3 or later as well as Mozilla Public License Version 2.
# Refer to the LICENSE.md file for details.
#

QT += qml quick
QT += location positioning
QT += quickcontrols2

macx {
    QT += widgets
    QT += macextras
    LIBS += -weak_framework ApplicationServices -weak_framework Cocoa
}
