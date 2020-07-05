#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QIODevice>
#include <QDomElement>
#include <QFile>
#include <QList>
#include <QMap>
#include "generalparse.h"

typedef QList<QMap<QString, QString>> List;

class DomParser : public QObject
{
    Q_OBJECT
public:
  DomParser();
  QDomDocument l_doc;
  List arr;
  void parse_files(const QStringList file_names);

private:
  int set_arr(List *arr, QDomDocument doc, QString name); // Обработка данных и запись в LIST
  int add_doc(QIODevice *device, QString name); // Парсинг XML файла с проверкой
signals:
  // Сигналы для общения внутри потока
  void s_error(int count);
  void s_status(int count);
  void s_error_list(QString message);
};

#endif // DOMPARSER_H
