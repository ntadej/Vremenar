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

#include "weather/Sources.h"
#include "application/Services.h"
#include "common/LocaleManager.h"
#include "settings/Settings.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrlQuery>

#include <stdexcept>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

Sources::Country Sources::countryFromString(const QString &country)
{
    if (country == "si"_L1) {
        return Sources::Slovenia;
    }
    if (country == "de"_L1) {
        return Sources::Germany;
    }
    if (country == "global"_L1) {
        return Sources::Global;
    }

    throw std::runtime_error("unknown country");
}

QString Sources::countryToString(Country country)
{
    switch (country) {
    case Slovenia:
        return u"si"_s;
    case Germany:
        return u"de"_s;
    case Global:
        return u"global"_s;
    }

    throw std::runtime_error("unknown country");
}

QString Sources::countryToLocalizedString(Country country)
{
    switch (country) {
    case Slovenia:
        return "ARSO (%1)"_L1.arg(QObject::tr("Slovenia"));
    case Germany:
        return "DWD (%1)"_L1.arg(QObject::tr("Germany"));
    case Global:
        return QObject::tr("Global");
    }

    return {};
}

QUrlQuery Sources::sourceQuery()
{
    const Settings settings;

    QUrlQuery query;
    query.addQueryItem(u"country"_s, countryToString(settings.weatherSource()));

    return query;
}

QUrlQuery Sources::sourceAndLocaleQuery()
{
    const Settings settings;

    QUrlQuery query;
    query.addQueryItem(u"country"_s, countryToString(settings.weatherSource()));
    QString locale;
    auto *manager = Services::getInstance().localeManager();
    if (manager != nullptr) {
        locale = manager->locale().split('_').first();
    }
    if (!locale.isEmpty()) {
        query.addQueryItem(u"language"_s, locale);
    }

    return query;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Sources.cpp"
// NOLINTEND
