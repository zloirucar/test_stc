#include "tablemodel.h"

TableModel::TableModel()
{

}

TableModel::TableModel(List arr, QMap<int, QString> map, int col, int row)
{
    l_arr = arr;
    l_map = map;
    l_col = col;
    l_row = row;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return l_row;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return l_col;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int col = index.column();
        QString ans = l_arr.at(row).value(l_map.value(col));
        return QVariant(ans);
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        return l_map.value(section);
    }
    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();

        QMap<QString, QString> m = l_arr.value(row);

        QString ed_val = l_map.value(index.column());
        m.find(ed_val).value() = value.toString();
        l_arr.replace(row, m);
        emit(dataChanged(index, index));

        return true;
    }
    return false;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row)
        l_arr.removeAt(position);
    endRemoveRows();
    return true;
}

List TableModel::get_arr()
{
    return l_arr;
}
