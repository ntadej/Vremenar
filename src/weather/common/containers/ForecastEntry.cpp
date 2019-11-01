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

#include "weather/common/containers/ForecastEntry.h"

namespace Vremenar
{

ForecastEntry::ForecastEntry(const QString &id,
                             QString title,
                             QString icon,
                             const QGeoCoordinate &coordinate,
                             qreal zoomLevel,
                             QObject *parent)
    : ListItem(parent),
      _title(std::move(title)),
      _icon(std::move(icon)),
      _coordinate(coordinate),
      _zoomLevel(zoomLevel)
{
    setId(id);
}

QString ForecastEntry::display() const
{
    return _title;
}

QVariant ForecastEntry::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case IconRole:
        return icon();
    case CoordinateRole:
        return QVariant::fromValue(coordinate());
    case ZoomLevelRole:
        return zoomLevel();
    }

    return QVariant();
}

} // namespace Vremenar
