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

#ifndef VREMENAR_LISTMODEL_H_
#define VREMENAR_LISTMODEL_H_

#include <memory>

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include <QtCore/QVariant>

#include "common/ListItem.h"

namespace Vremenar
{

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModel(QHash<int, QByteArray> roleNames,
                       QObject *parent = nullptr);

    [[nodiscard]] QVariant data(const QModelIndex &index,
                                int role) const override;
    // NOLINTNEXTLINE(google-default-arguments)
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // NOLINTNEXTLINE(google-default-arguments)
    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override { return _roleNames; }

    template <class T>
    T *appendRow(std::unique_ptr<T> item)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        connect(item.get(), &T::dataChanged, this, &ListModel::handleItemChange);
        _list.push_back(std::move(item));
        endInsertRows();
        return qobject_cast<T *>(_list.back().get());
    }

    bool removeRow(int row,
                   const QModelIndex &parent = QModelIndex());

    template <class T>
    std::unique_ptr<T> takeRow(int row)
    {
        beginRemoveRows(QModelIndex(), row, row);
        std::unique_ptr<T> item = nullptr;
        item.swap(_list.at(static_cast<size_t>(row)));
        _list.erase(_list.begin() + row);
        endRemoveRows();
        return item;
    }

    template <class T>
    T *row(int row)
    {
        return qobject_cast<T *>(_list[static_cast<size_t>(row)].get());
    }

    template <class T>
    const T *row(int row) const
    {
        return qobject_cast<T *>(_list[static_cast<size_t>(row)].get());
    }

    template <class T>
    [[nodiscard]] T *find(const QString &id) const
    {
        for (const auto &item : _list) {
            if (item->id() == id) {
                return qobject_cast<T *>(item.get());
            }
        }
        return nullptr;
    }

    QModelIndex indexFromItem(const ListItem *item) const;
    void clear();

private slots:
    void handleItemChange();

private:
    const QHash<int, QByteArray> _roleNames;

    std::vector<std::unique_ptr<ListItem>> _list;
};

} // namespace Vremenar

#endif // VREMENAR_LISTMODEL_H_
