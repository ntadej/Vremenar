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

#include "weather/api/APISources.h"

#include "application/Services.h"
#include "common/LocaleManager.h"
#include "settings/Settings.h"
#include "weather/Weather.h"

#include <QtCore/QLocale>
#include <QtCore/QString>
#include <QtCore/QUrlQuery>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

QUrlQuery API::sourceQuery()
{
    const Settings settings;

    QUrlQuery query;
    query.addQueryItem(u"country"_s, Weather::sourceToString(settings.weatherSource()));

    return query;
}

QUrlQuery API::sourceAndLocaleQuery()
{
    const Settings settings;

    QUrlQuery query;
    query.addQueryItem(u"country"_s, Weather::sourceToString(settings.weatherSource()));
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
