#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QTableView>
#include <QIODevice>
#include <QDomElement>
#include <QFile>
#include <QList>
#include <QMap>
#include "importdialog.h"

typedef QList<QMap<QString, QString>> List;

class DomParser
{
public:
  DomParser();
  DomParser(ImportDialog *dial);
  QDomDocument l_doc;
  List arr;
  void parse_files(const QStringList file_names);

private:
  void  set_arr(List *arr, QDomDocument doc);
  int   add_doc(QIODevice *device, QString name);
  ImportDialog *l_dial;
};

#endif // DOMPARSER_H
