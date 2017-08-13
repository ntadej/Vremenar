/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LISTMODEL_H_
#define VREMENAR_LISTMODEL_H_

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QVariant>

class ListItem;

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListModel(ListItem *prototype, QObject *parent = 0);
    ~ListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void appendRow(ListItem *item);
    void appendRows(const QList<ListItem *> &items);
    void insertRow(int row, ListItem *item);
    bool moveRow(int oldRow, int newRow, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    ListItem *row(int row);
    ListItem *takeRow(int row);
    ListItem *find(const QString &id) const;
    QModelIndex indexFromItem(const ListItem *item) const;
    void clear();

private slots:
    void handleItemChange();

private:
    ListItem *_prototype;
    QList<ListItem *> _list;
};

#endif // VREMENAR_LISTMODEL_H_
