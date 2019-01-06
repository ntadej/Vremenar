/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
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

#include "common/ListItem.h"

namespace Vremenar
{

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListModel(std::unique_ptr<ListItem> prototype,
              QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const override;
    virtual bool removeRows(int row,
                            int count,
                            const QModelIndex &parent = QModelIndex()) override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ListItem *appendRow(std::unique_ptr<ListItem> item);
    ListItem *insertRow(int row,
                        std::unique_ptr<ListItem> item);
    bool removeRow(int row,
                   const QModelIndex &parent = QModelIndex());
    std::unique_ptr<ListItem> takeRow(int row);

    ListItem *row(int row);
    ListItem *find(const QString &id) const;

    QModelIndex indexFromItem(const ListItem *item) const;

    void clear();

private slots:
    void handleItemChange();

private:
    std::unique_ptr<ListItem> _prototype;
    std::vector<std::unique_ptr<ListItem>> _list;
};

} // namespace Vremenar

#endif // VREMENAR_LISTMODEL_H_
