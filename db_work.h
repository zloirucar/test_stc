#ifndef DB_WORK_H
#define DB_WORK_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QMapIterator>
#include <QMap>
#include <QVariant>
#include <QDir>

typedef QList<QMap<QString, QString>> List;

class db_work : public QObject
{
    Q_OBJECT
public:
    db_work();
    db_work(List *status);
    int get_row() const;
    int get_col() const;
    void get_data();
    void set_arr(List new_arr);
    void set_data(List arr);
    List get_arr() const;
    QMap<int, QString> get_map() const;
private:
    QMap<QString, QString> l_map;
    List arr;
    QMap<int,QString> map;
    int l_row;
    int l_col;
public slots:
    void do_Work(); // Слот для отправки в поток при импорте
    void do_Work_ch(); // Слот для изменения в БД
signals:
    void finished();
    void db_done();
};

#endif // DB_WORK_H
