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

#ifndef VREMENAR_LISTITEM_H_
#define VREMENAR_LISTITEM_H_

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Vremenar
{

class ListItem : public QObject
{
    Q_OBJECT
public:
    explicit ListItem(QObject *parent = nullptr) : QObject(parent) {}

    inline const QString &id() const { return _id; }

    virtual QVariant data(int role) const = 0;
    virtual QString display() const = 0;

Q_SIGNALS:
    void dataChanged();

protected:
    void setId(const QString &id) { _id = id; }

private:
    QString _id;
};

} // namespace Vremenar

#endif // VREMENAR_LISTITEM_H_
