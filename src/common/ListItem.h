/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LISTITEM_H_
#define VREMENAR_LISTITEM_H_

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QVariant>

class ListItem : public QObject
{
    Q_OBJECT
public:
    ListItem(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ListItem() {}

    virtual QString id() const = 0;
    virtual QVariant data(int role) const = 0;
    virtual QString display() const = 0;
    virtual QHash<int, QByteArray> roleNames() const = 0;

signals:
    void dataChanged();
};

#endif // VREMENAR_LISTITEM_H_
