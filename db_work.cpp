#include "db_work.h"

db_work::db_work()
{
}

db_work::db_work(List *status)
{
    arr = *status;
}

void db_work::get_data()
{
    QSqlDatabase db;
    l_row = 0;
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString name = QDir::currentPath() + "//xml_reader.db";
    QFile file(name);
    db.setDatabaseName(name);
    if(!file.exists())
    {
        db.open();
        QSqlQuery q;
        q.exec("CREATE TABLE \"test_db\" (\
               \"texteditor\"	TEXT,\
               \"cancompile\"	TEXT,\
               \"encoding\"	TEXT,\
               \"hasplugins\"	TEXT,\
               \"fileformats\"	TEXT,\
               \"hasintellisense\"	TEXT\
               )");
    }
    else
        db.open();
    QStringList headers = {"texteditor", "cancompile", "encoding", "hasplugins", "fileformats", "hasintellisense"};
    for (int i = 0; i < headers.length(); i++)
        map.insert(i,headers.at(i));
    QSqlQuery query;
    l_col = headers.length();
    query.exec("SELECT texteditor, cancompile, encoding, hasplugins, fileformats, hasintellisense FROM test_db");
    while(query.next())
    {
        int i = 0;
        while (i < headers.length())
        {
            QString tag = headers.at(i);
            QString text = query.value(i).toString();
            l_map.insert(tag, text);
            i++;
        }
        arr.append(l_map);
        l_row++;
    }
    db.close();
    emit db_done();
}

void db_work::set_arr(List new_arr)
{
    arr = new_arr;
}

void db_work::set_data(List arr)
{
    QSqlDatabase db3;
    QStringList headers = {"texteditor", "cancompile", "encoding", "hasplugins", "fileformats", "hasintellisense"};
    db3 = QSqlDatabase::addDatabase("QSQLITE");
    db3.setDatabaseName(QDir::currentPath() + "//xml_reader.db");
    db3.open();
    l_row = arr.length();
    for (int i = 0; i < l_row; i++)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO test_db (texteditor, cancompile, encoding, hasplugins, fileformats, hasintellisense)"
                      "VALUES(:texteditor, :cancompile, :encoding, :hasplugins, :fileformats, :hasintellisense)");
        for (int j = 0; j < headers.length(); j++)
        {
            QString val = arr.at(i).value(headers.at(j));
            QString head = ":" + headers.at(j);
            query.bindValue(head, val);
        }
        query.exec();
    }
    db3.close();
}

List db_work::get_arr() const
{
    return arr;
}

QMap<int, QString> db_work::get_map() const
{
    return map;
}

void db_work::do_Work()
{
    set_data(arr);
    arr.clear();
    get_data();
    emit finished();
}

void db_work::do_Work_ch()
{
    QSqlDatabase db2;
    db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName(QDir::currentPath() + "//xml_reader.db");
    db2.open();
    QSqlQuery query;
    query.exec("DELETE FROM test_db");
    db2.close();
    db2.removeDatabase(QSqlDatabase::defaultConnection);
    set_data(arr);
    arr.clear();
    get_data();
    emit finished();
}

int db_work::get_row() const
{
    return l_row;
}

int db_work::get_col() const
{
    return l_col;
}
