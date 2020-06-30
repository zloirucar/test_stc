#ifndef FILE_READER_H
#define FILE_READER_H

#include <QDir>
#include <QList>
#include "importdialog.h"

class File_Reader:public QObject
{
    Q_OBJECT
public:
    File_Reader();
    File_Reader(const QString &path, ImportDialog *dial);
    QStringList find_files;
private:
    int check_file(const QString &fileName);
    void get_files(const QString &path);
    int error_count = 0;
    int suc_count = 0;
    ImportDialog *l_dial;

};

#endif // FILE_READER_H
