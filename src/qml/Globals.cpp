/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/Common.h"
#include "location/LocationProvider.h"
#include "settings/Settings.h"

#include "qml/Globals.h"

QString Globals::name() const { return Vremenar::name(); }
QString Globals::version() const { return Vremenar::version(); }
int Globals::build() const { return Vremenar::build(); }

QString Globals::mapboxAPIToken() const { return Vremenar::LocationProvider::mapboxAPIToken(); }

QObject *Globals::provider(QQmlEngine *engine,
                           QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Globals;
}

QObject *Globals::providerSettings(QQmlEngine *engine,
                                   QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Settings;
}
