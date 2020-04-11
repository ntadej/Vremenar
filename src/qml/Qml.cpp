/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtQuick/QQuickItem>

#include "qml/Globals.h"
#include "qml/UIManager.h"

#include "common/Enums.h"
#include "settings/Settings.h"
#include "weather/common/Weather.h"

#include "qml/Qml.h"

namespace Vremenar
{

void Qml::registerTypes()
{
    const char *uri = "Vremenar";

    qmlRegisterSingletonType<Globals>(uri, 1, 0, "Globals", Globals::provider);
    qmlRegisterSingletonType<UIManager>(uri, 1, 0, "UI", UIManager::provider);
    qmlRegisterSingletonType<Settings>(uri, 1, 0, "Settings", Globals::providerSettings);

    qmlRegisterUncreatableMetaObject(Common::staticMetaObject, uri, 1, 0, "Common", "Error: only enums");
    qmlRegisterUncreatableMetaObject(Weather::staticMetaObject, uri, 1, 0, "Weather", "Error: only enums");
}

} // namespace Vremenar
