#ifndef FILE_READER_H
#define FILE_READER_H

#include <QDir>
#include <QList>
#include "generalparse.h"

class File_Reader : public QObject
{
    Q_OBJECT
public:
    File_Reader();
    File_Reader(QString path);
    QStringList find_files;
    void get_files(const QString &path);
private:
    QString l_path;
    int check_file(const QString &fileName); // Проверка на права доступа к файлу
    int error_count = 0;
    int suc_count = 0;
signals:
    // Сигналы для общения внутри потока
    void s_error(int count);
    void s_status(int count);
    void s_error_list(QString message);
};

#endif // FILE_READER_H
