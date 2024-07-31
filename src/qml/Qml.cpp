/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "qml/Qml.h"

#include "common/Enums.h"
#include "qml/Globals.h"
#include "qml/UIManager.h"
#include "settings/Settings.h"
#include "weather/Weather.h"
#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"

#include <QtCore/QString>
#include <QtQml/qqml.h>
#include <QtQuick/QQuickItem>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

void Qml::registerTypes()
{
    const char *uri = "Vremenar";

    qmlRegisterSingletonType<Globals>(uri, 1, 0, "Globals", Globals::provider);
    qmlRegisterSingletonType<UIManager>(uri, 1, 0, "UI", UIManager::provider);
    qmlRegisterSingletonType<Settings>(uri, 1, 0, "Settings", Globals::providerSettings);

    qmlRegisterUncreatableType<StationInfo>(uri, 1, 0, "StationInfo", u"Error: only creatable in C++"_s);
    qmlRegisterUncreatableType<WeatherCondition>(uri, 1, 0, "WeatherCondition", u"Error: only creatable in C++"_s);

    qmlRegisterUncreatableMetaObject(Common::staticMetaObject, uri, 1, 0, "Common", u"Error: only enums"_s);
    qmlRegisterUncreatableMetaObject(Weather::staticMetaObject, uri, 1, 0, "Weather", u"Error: only enums"_s);
}

} // namespace Vremenar
