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

#ifndef VREMENAR_STATIONLISTITEM_H_
#define VREMENAR_STATIONLISTITEM_H_

#include <memory>

#include <QtCore/QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "common/ListItem.h"

namespace Vremenar
{

class StationListItem : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        EditRole = Qt::EditRole,
        IdRole = Qt::UserRole + 1,
        CoordinateRole
    };

    explicit StationListItem(const QString &id,
                             QString name,
                             const QGeoCoordinate &coordinate,
                             QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] static std::unique_ptr<StationListItem> fromJson(const QJsonObject &json);

    [[nodiscard]] inline const QGeoCoordinate &coordinate() const { return _coordinate; }

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {EditRole, "edit"},
            {CoordinateRole, "coordinate"}};
    }

private:
    QString _name;
    QGeoCoordinate _coordinate;
};

} // namespace Vremenar

Q_DECLARE_METATYPE(Vremenar::StationListItem *)

#endif // VREMENAR_STATIONLISTITEM_H_
