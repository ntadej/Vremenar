/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "ListItem.h"

#include "ListModel.h"

namespace Vremenar
{

ListModel::ListModel(std::unique_ptr<ListItem> prototype,
                     QObject *parent)
    : QAbstractListModel(parent),
      _prototype(std::move(prototype)) {}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(_list.size());
}

QVariant ListModel::data(const QModelIndex &index,
                         int role) const
{
    auto i = static_cast<size_t>(index.row());
    if (index.row() < 0 || i >= _list.size())
        return QVariant();
    return _list[i]->data(role);
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return _prototype->roleNames();
}

void ListModel::appendRow(std::unique_ptr<ListItem> item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    connect(item.get(), &ListItem::dataChanged, this, &ListModel::handleItemChange);
    _list.push_back(std::move(item));
    endInsertRows();
}

void ListModel::insertRow(int row,
                          std::unique_ptr<ListItem> item)
{
    beginInsertRows(QModelIndex(), row, row);
    connect(item.get(), &ListItem::dataChanged, this, &ListModel::handleItemChange);
    _list.insert(_list.begin() + row, std::move(item));
    endInsertRows();
}

void ListModel::handleItemChange()
{
    auto *item = qobject_cast<ListItem *>(sender());
    QModelIndex index = indexFromItem(item);
    if (index.isValid())
        emit dataChanged(index, index);
}

ListItem *ListModel::find(const QString &id) const
{
    for (const std::unique_ptr<ListItem> &item : _list) {
        if (item->id() == id)
            return item.get();
    }
    return nullptr;
}

QModelIndex ListModel::indexFromItem(const ListItem *item) const
{
    Q_ASSERT(item);
    for (size_t row = 0; row < _list.size(); ++row) {
        if (_list[row].get() == item)
            return index(static_cast<int>(row));
    }
    return {};
}

void ListModel::clear()
{
    removeRows(0, rowCount());
}

bool ListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (row < 0 || static_cast<size_t>(row) >= _list.size())
        return false;
    beginRemoveRows(QModelIndex(), row, row);
    _list.erase(_list.begin() + row);
    endRemoveRows();
    return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    int toRemove = row + count;
    if (row < 0 || static_cast<size_t>(toRemove) > _list.size())
        return false;
    beginRemoveRows(QModelIndex(), row, toRemove - 1);
    for (int i = 0; i < count; ++i) {
        _list.erase(_list.begin() + row);
    }
    endRemoveRows();
    return true;
}

ListItem *ListModel::row(int row)
{
    return _list[static_cast<size_t>(row)].get();
}

std::unique_ptr<ListItem> ListModel::takeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    std::unique_ptr<ListItem> item = nullptr;
    item.swap(_list.at(static_cast<size_t>(row)));
    _list.erase(_list.begin() + row);
    endRemoveRows();
    return item;
}

} // namespace Vremenar
