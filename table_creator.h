#ifndef TABLE_CREATOR_H
#define TABLE_CREATOR_H

#include "QStandardItemModel"
#include "QStandardItem"
#include <QMapIterator>
#include <QMap>


typedef QList<QMap<QString, QString>> List;

class Table_Creator
{
public:
    Table_Creator();
    QStandardItemModel  *init_table(List arr);
private:
    int find_vert(QString key, QStringList vert);
};

#endif // TABLE_CREATOR_H
