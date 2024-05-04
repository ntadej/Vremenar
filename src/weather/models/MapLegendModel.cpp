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

#include "weather/models/MapLegendModel.h"

#include "common/ListModel.h"
#include "weather/Weather.h"
#include "weather/containers/MapLegendItem.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringLiteral>

#include <memory>
#include <utility>

namespace Vremenar
{

MapLegendModel::MapLegendModel(QObject *parent)
    : ListModel(MapLegendItem::roleNames(), parent) {}

void MapLegendModel::addMapLegends(const QJsonArray &data)
{
    for (const auto &legendRef : data) {
        const QJsonObject legend = legendRef.toObject();
        const auto type = Weather::mapTypeFromString(legend[QStringLiteral("map_type")].toString());
        if (type == Weather::MapType::UnknownMapType) {
            continue;
        }

        const QJsonArray list = legend[QStringLiteral("items")].toArray();
        for (const auto &itemRef : list) {
            const QJsonObject item = itemRef.toObject();

            QString value = item[QStringLiteral("value")].toString();
            if (item.contains(QStringLiteral("translatable")) && item[QStringLiteral("translatable")].toBool()) {
                value = translate(value);
            }
            const QString color = item[QStringLiteral("color")].toString();
            bool placeholder{};
            if (item.contains(QStringLiteral("placeholder"))) {
                placeholder = item[QStringLiteral("placeholder")].toBool();
            }

            emplace(type, value, color, placeholder);
        }
    }
}

MapLegendItem *MapLegendModel::emplace(Weather::MapType type,
                                       const QString &value,
                                       const QColor &color,
                                       bool placeholder)
{
    auto item = std::make_unique<MapLegendItem>(type, value, color, placeholder);
    return appendRow(std::move(item));
}

QString MapLegendModel::translate(const QString &string)
{
    static const QMap<QString, const char *> translations = {
        {QString("low"), QT_TR_NOOP("low")},
        {QString("moderate"), QT_TR_NOOP("moderate")},
        {QString("large"), QT_TR_NOOP("large")},
        {QString("probability"), QT_TR_NOOP("probability")}};
    return tr(translations[string]);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_MapLegendModel.cpp"
// NOLINTEND
