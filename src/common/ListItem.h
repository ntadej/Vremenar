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

#ifndef VREMENAR_LISTITEM_H_
#define VREMENAR_LISTITEM_H_

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

namespace Vremenar
{

class ListItem : public QObject
{
    Q_OBJECT
public:
    explicit ListItem(QObject *parent = nullptr) : QObject(parent) {}

    [[nodiscard]] const QString &id() const { return _itemId; }

    [[nodiscard]] virtual QVariant data(int role) const = 0;
    [[nodiscard]] virtual QString display() const = 0;

signals:
    void dataChanged();

protected:
    void setId(const QString &id) { _itemId = id; }

private:
    QString _itemId;
};

} // namespace Vremenar

#endif // VREMENAR_LISTITEM_H_
