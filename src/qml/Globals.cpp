/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "qml/Globals.h"

#include "common/About.h"
#include "common/containers/Hyperlink.h"
#include "maps/MapsCommon.h"
#include "settings/Settings.h"

#include "Config.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>

#include <memory>

namespace Vremenar
{

QString Qml::Globals::name() const { return Vremenar::name; }
QString Qml::Globals::version() const { return Vremenar::version; }
int Qml::Globals::build() const { return Vremenar::build; }

QString Qml::Globals::mapsStyle() const { return Vremenar::mapsEndpoint; }

QJsonArray Qml::Globals::mapsCopyright() const
{
    QJsonArray list;
    for (const std::unique_ptr<Hyperlink> &link : Maps::copyright()) {
        list.append(link->asJson());
    }
    return list;
}

QJsonArray Qml::Globals::aboutLinks() const
{
    QJsonArray list;
    for (const std::unique_ptr<Hyperlink> &link : Vremenar::aboutLinks()) {
#if !defined(Q_OS_IOS) && !defined(Q_OS_ANDROID)
        if (link->mobileOnly()) {
            continue;
        }
#endif
        list.append(link->asJson());
    }
    return list;
}

QObject *Qml::Globals::provider(QQmlEngine *engine,
                                QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Globals; // NOLINT(cppcoreguidelines-owning-memory)
}

QObject *Qml::Globals::providerSettings(QQmlEngine *engine,
                                        QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Settings; // NOLINT(cppcoreguidelines-owning-memory)
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Globals.cpp"
// NOLINTEND
