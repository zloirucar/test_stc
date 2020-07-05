#include "file_reader.h"

File_Reader::File_Reader()
{

}

File_Reader::File_Reader(QString path)
{
    l_path = path;
}

int File_Reader::check_file(const QString &fileName) {
    QFile file(fileName);
    if (!file.exists())
        return(-2);
    if (!file.open(QIODevice::ReadOnly))
        return(-3);
    else
        file.close();
    return  (1);
}

void File_Reader::get_files(const QString &path)
{
    QDir dir(path);
    QStringList filters;
    filters << "*.xml";
    dir.setNameFilters(filters);
    QStringList files = dir.entryList();
    QStringListIterator iter(files);
    iter.toFront();
    while (iter.hasNext())
    {
        QString name_file = iter.next();
        int result = check_file(dir.filePath(name_file));
        if (result < 0)
        {
            File_Reader::error_count++;
            emit s_error_list(QString("Not open file:" + name_file + "\n"));
            emit s_error(error_count);
        }
        else
        {
            find_files.append(dir.filePath(name_file));
            File_Reader::suc_count++;
            emit  s_status(suc_count);
        }
    }
}
