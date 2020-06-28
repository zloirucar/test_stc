#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QTableView>
#include <QIODevice>
#include <QDomElement>
#include <QFile>
#include <QList>
#include <QMap>

class DomParser
{
public:
  DomParser(QIODevice *device, QTableView *view);
  void test(QList<QMap<QString, QString>> *arr, QDomDocument l_doc);
  QDomDocument l_doc;
  QList<QMap<QString, QString>> arr;

private:


  void set_arr(QList<QMap<QString, QString>> *arr, QDomDocument doc);
  // void parseFile(const QString &fileName);
};

#endif // DOMPARSER_H
