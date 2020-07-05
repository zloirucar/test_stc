#ifndef EXPORTFILE_H
#define EXPORTFILE_H
#include <QXmlStreamWriter>
#include <QFile>
#include "importdialog.h"
#include <QTableView>
#include <QDir>

class ExportFile
{
public:
    ExportFile(int col_count, QTableView *table);
    void write_code(); //Обработка строки таблицы для экспорта в XML
    //XML отправляется в папсу с исполняемым файлом
private:
    void set_tag(QXmlStreamWriter *document);
    QTableView *l_table;
    int l_count; // количество колонок в таблице
};

#endif // EXPORTFILE_H
