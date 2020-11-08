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

#include "settings/Settings.h"

#include "weather/Sources.h"

namespace Vremenar
{

Sources::Country Sources::countryFromString(const QString &country)
{
    if (country == QStringLiteral("si")) {
        return Sources::Slovenia;
    }
    if (country == QStringLiteral("de")) {
        return Sources::Germany;
    }

    throw std::runtime_error("unknown country");
}

QString Sources::countryToString(Country country)
{
    switch (country) {
    case Slovenia:
        return QStringLiteral("si");
    case Germany:
        return QStringLiteral("de");
    }

    throw std::runtime_error("unknown country");
}

QString Sources::countryToLocalizedString(Country country)
{
    switch (country) {
    case Slovenia:
        return QStringLiteral("ARSO (%1)").arg(QObject::tr("Slovenia"));
    case Germany:
        return QStringLiteral("DWD (%1)").arg(QObject::tr("Germany"));
    }

    return QString();
}

QUrlQuery Sources::sourceQuery()
{
    Settings settings;

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), countryToString(settings.weatherSource()));

    return query;
}

} // namespace Vremenar
