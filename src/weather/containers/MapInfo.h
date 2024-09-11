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

#ifndef VREMENAR_MAPINFO_H_
#define VREMENAR_MAPINFO_H_

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <cstdint>

namespace Vremenar
{

class MapInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(Weather::MapType type READ type CONSTANT)
public:
    enum Roles : std::uint16_t {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        SourceRole,
        TypeRole
    };

    explicit MapInfo(Weather::Source source,
                     Weather::MapType type,
                     QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] Weather::Source source() const { return _source; }
    [[nodiscard]] Weather::MapType type() const { return _type; }

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {SourceRole, "source"},
            {TypeRole, "type"}};
    }

private:
    Weather::Source _source{Weather::Global};
    Weather::MapType _type{Weather::UnknownMapType};
    QString _description;
};

} // namespace Vremenar

#endif // VREMENAR_MAPINFO_H_
