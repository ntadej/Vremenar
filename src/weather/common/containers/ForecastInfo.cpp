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

#include "weather/common/containers/ForecastInfo.h"

namespace Vremenar
{

ForecastInfo::ForecastInfo(QString url,
                           QDateTime time,
                           QObject *parent)
    : ListItem(parent),
      _url(std::move(url)),
      _time(std::move(time))
{
    setId(_time.toString());
}

QString ForecastInfo::display() const
{
    return id();
}

QVariant ForecastInfo::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case UrlRole:
        return url();
    case TimeRole:
        return time();
    default:
        return QVariant();
    }
}

} // namespace Vremenar
