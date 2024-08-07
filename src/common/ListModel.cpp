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

#include "ListModel.h"

#include "ListItem.h"

#include <QtCore/QAbstractListModel>
#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QVariant>

#include <cstddef>
#include <utility>
#include <vector>

namespace Vremenar
{

ListModel::ListModel(QHash<int, QByteArray> roleNames,
                     QObject *parent)
    : QAbstractListModel(parent),
      _roleNames(std::move(roleNames)) {}

// NOLINTNEXTLINE(google-default-arguments)
int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(_list.size());
}

QVariant ListModel::data(const QModelIndex &index,
                         int role) const
{
    auto i = static_cast<std::size_t>(index.row());
    if (index.row() < 0 || i >= _list.size()) {
        return {};
    }
    return _list[i]->data(role);
}

void ListModel::handleItemChange()
{
    auto *item = qobject_cast<ListItem *>(sender());
    const QModelIndex index = indexFromItem(item);
    if (index.isValid()) {
        emit dataChanged(index, index);
    }
}

void ListModel::clear()
{
    if (!_list.empty()) {
        removeRows(0, rowCount());
    }
}

bool ListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    if (row < 0 || static_cast<std::size_t>(row) >= _list.size()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), row, row);
    _list.erase(_list.begin() + row);
    endRemoveRows();
    return true;
}

// NOLINTNEXTLINE(google-default-arguments)
bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    const int toRemove = row + count;
    if (row < 0 || static_cast<std::size_t>(toRemove) > _list.size()) {
        return false;
    }
    beginRemoveRows(QModelIndex(), row, toRemove - 1);
    for (int i = 0; i < count; ++i) {
        _list.erase(_list.begin() + row);
    }
    endRemoveRows();
    return true;
}

QModelIndex ListModel::indexFromItem(const ListItem *item) const
{
    Q_ASSERT(item);
    for (std::size_t row = 0; row < _list.size(); ++row) {
        if (_list[row].get() == item) {
            return index(static_cast<int>(row));
        }
    }
    return {};
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_ListModel.cpp"
// NOLINTEND
