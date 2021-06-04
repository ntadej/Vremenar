/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/containers/StationListItem.h"

namespace Vremenar
{

StationListItem::StationListItem(const QString &id,
                                 QString name,
                                 QObject *parent)
    : ListItem(parent),
      _name(std::move(name))
{
    setId(id);
}

std::unique_ptr<StationListItem> StationListItem::fromJson(const QJsonObject &json)
{
    QString id = json[QStringLiteral("id")].toString();
    QString name = json[QStringLiteral("name")].toString();

    return std::make_unique<StationListItem>(id, name);
}

QString StationListItem::display() const
{
    return _name;
}

QVariant StationListItem::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    }

    return QVariant();
}

} // namespace Vremenar
