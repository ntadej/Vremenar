/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "ListItem.h"
#include "ListModel.h"

ListModel::ListModel(ListItem *prototype,
                     QObject *parent)
    : QAbstractListModel(parent),
      _prototype(prototype) {}

ListModel::~ListModel()
{
    delete _prototype;
    clear();
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _list.size();
}

QVariant ListModel::data(const QModelIndex &index,
                         int role) const
{
    if (index.row() < 0 || index.row() >= _list.size())
        return QVariant();
    return _list[index.row()]->data(role);
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return _prototype->roleNames();
}

void ListModel::appendRow(ListItem *item)
{
    appendRows(QList<ListItem *>() << item);
}

void ListModel::appendRows(const QList<ListItem *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
    foreach (ListItem *item, items) {
        connect(item, &ListItem::dataChanged, this, &ListModel::handleItemChange);
        _list.append(item);
    }
    endInsertRows();
}

void ListModel::insertRow(int row, ListItem *item)
{
    beginInsertRows(QModelIndex(), row, row);
    connect(item, &ListItem::dataChanged, this, &ListModel::handleItemChange);
    _list.insert(row, item);
    endInsertRows();
}

void ListModel::handleItemChange()
{
    ListItem *item = qobject_cast<ListItem *>(sender());
    QModelIndex index = indexFromItem(item);
    if (index.isValid())
        emit dataChanged(index, index);
}

ListItem *ListModel::find(const QString &id) const
{
    foreach (ListItem *item, _list) {
        if (item->id() == id)
            return item;
    }
    return 0;
}

QModelIndex ListModel::indexFromItem(const ListItem *item) const
{
    Q_ASSERT(item);
    for (int row = 0; row < _list.size(); ++row) {
        if (_list[row] == item)
            return index(row);
    }
    return QModelIndex();
}

void ListModel::clear()
{
    removeRows(0, rowCount());
}

bool ListModel::moveRow(int oldRow, int newRow, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (oldRow < 0 || oldRow >= _list.size() || newRow < 0 || newRow >= _list.size())
        return false;
    beginMoveRows(QModelIndex(), oldRow, oldRow, QModelIndex(), newRow);
    _list.move(oldRow, newRow);
    endMoveRows();
    return true;
}

bool ListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row < 0 || row >= _list.size())
        return false;
    beginRemoveRows(QModelIndex(), row, row);
    delete _list.takeAt(row);
    endRemoveRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row < 0 || (row + count) > _list.size())
        return false;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        delete _list.takeAt(row);
    }
    endRemoveRows();
    return true;
}

ListItem *ListModel::row(int row)
{
    ListItem *item = _list[row];
    return item;
}

ListItem *ListModel::takeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    ListItem *item = _list.takeAt(row);
    endRemoveRows();
    return item;
}
