#ifndef GENEARLPARSE_H
#define GENEARLPARSE_H

#include <QObject>
#include "importdialog.h"
#include "file_reader.h"
#include "domparser.h"
#include <QFileDialog>

typedef QList<QMap<QString, QString>> List;

class GeneralParse : public QObject
{
    Q_OBJECT
public:
    GeneralParse(QString str);
    List arr;
signals:
    void finished();
    //Сигналы для отправки в основной поток
    void send_to_open_error(int count);
    void send_to_open_status(int count);
    void send_to_error_list(QString message);
    void send_to_parse_error(int count);
    void send_to_parse_status(int count);
    void send_arr(List done_arr);

public slots:
    void doParse(); // слот для старта парса с открытием потока
    //Слоты для принятия сигналов из парсеров
    void reader_error(int count);
    void reader_status(int count);
    void parse_error(int count);
    void parse_open(int count);
    void error_list(QString message);

private:
    QString l_str;
};

#endif // GENEARLPARSE_H
