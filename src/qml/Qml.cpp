/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtQuick/QQuickItem>

#include "qml/Globals.h"
#include "qml/Qml.h"
#include "settings/Settings.h"

void Vremenar::Qml::registerTypes()
{
    const char *uri = "Vremenar";

    qmlRegisterSingletonType<Globals>(uri, 1, 0, "Globals", Globals::provider);
    qmlRegisterSingletonType<Settings>(uri, 1, 0, "Settings", Globals::providerSettings);
}
