#ifndef FILE_READER_H
#define FILE_READER_H

#include <QDir>
#include <QList>

class File_Reader
{
public:
    File_Reader(const QString &path);
    QStringList error_open;
    QStringList find_files;
private:
    int check_file(const QString &fileName);
    void get_files(const QString &path);
};

#endif // FILE_READER_H
