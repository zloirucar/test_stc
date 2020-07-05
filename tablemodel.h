#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <db_work.h>


class TableModel : public QAbstractTableModel
{
public:
    TableModel();
    TableModel(List arr, QMap<int, QString> map, int col, int row);

    // Определение методов для создания модели таблицы
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRows(int position, int rows, const QModelIndex &index);
    List get_arr();
private:
    List l_arr;
    QMap<int, QString> l_map;
    int l_col = 0;
    int l_row = 0;
};

#endif // TABLEMODEL_H
