#ifndef TABLE_CREATOR_H
#define TABLE_CREATOR_H

#include "QStandardItemModel"
#include "QStandardItem"
#include <QMapIterator>
#include <QMap>

class Table_Creator
{
public:
    Table_Creator();
    QStandardItemModel  *init_table(QList<QMap<QString, QString>> arr);
private:
    int find_vert(QString key, QStringList vert);
};

#endif // TABLE_CREATOR_H
