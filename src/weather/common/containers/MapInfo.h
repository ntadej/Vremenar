/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MAPINFO_H_
#define VREMENAR_MAPINFO_H_

#include "common/ListItem.h"
#include "weather/common/Weather.h"

namespace Vremenar
{

class MapInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(Weather::MapType type READ type CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        TypeRole
    };

    explicit MapInfo(Weather::MapType type,
                     QObject *parent = nullptr);

    // Implemented virtual functions
    virtual QVariant data(int role) const final;
    virtual QString display() const final;

    inline Weather::MapType type() const { return _type; }

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {TypeRole, "type"}};
    }

private:
    Weather::MapType _type;
    QString _description;
};

} // namespace Vremenar

#endif // VREMENAR_MAPINFO_H_
