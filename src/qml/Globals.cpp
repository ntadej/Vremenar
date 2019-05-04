/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/Common.h"
#include "location/LocationProvider.h"
#include "settings/Settings.h"

#include "qml/Globals.h"

namespace Vremenar
{

QString Qml::Globals::name() const { return Vremenar::name(); }
QString Qml::Globals::version() const { return Vremenar::version(); }
int Qml::Globals::build() const { return Vremenar::build(); }

QString Qml::Globals::mapsStyle() const { return LocationProvider::mapsStyle(); }

QObject *Qml::Globals::provider(QQmlEngine *engine,
                                QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Globals;
}

QObject *Qml::Globals::providerSettings(QQmlEngine *engine,
                                        QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Settings;
}

} // namespace Vremenar
