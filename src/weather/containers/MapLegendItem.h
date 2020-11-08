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

#ifndef VREMENAR_MAPLEGENDITEM_H_
#define VREMENAR_MAPLEGENDITEM_H_

#include <QtGui/QColor>

#include "common/ListItem.h"
#include "weather/Weather.h"

namespace Vremenar
{

class MapLegendItem : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(Weather::MapType type READ type CONSTANT)
    Q_PROPERTY(QColor color READ color CONSTANT)
    Q_PROPERTY(bool placeholder READ placeholder CONSTANT)

public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        TypeRole,
        ColorRole,
        PlaceholderRole
    };

    explicit MapLegendItem(Weather::MapType type,
                           QString value,
                           QColor color,
                           bool placeholder = false,
                           QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] inline Weather::MapType type() const { return _type; }
    [[nodiscard]] inline const QColor &color() const { return _color; }
    [[nodiscard]] inline bool placeholder() const { return _placeholder; }

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {TypeRole, "type"},
            {ColorRole, "color"},
            {PlaceholderRole, "placeholder"}};
    }

private:
    Weather::MapType _type{Weather::UnknownMapType};
    QString _value;
    QColor _color;
    bool _placeholder;
};

} // namespace Vremenar

#endif // VREMENAR_MAPLEGENDITEM_H_
