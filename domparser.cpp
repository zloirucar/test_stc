#include "domparser.h"

DomParser::DomParser()
{
}

void DomParser::parse_files(const QStringList file_names)
{
    int count_suc = 0;
    int count_err = 0;
    QStringListIterator iter(file_names);
    iter.toFront();
    while(iter.hasNext())
    {
        QString name = iter.next();
        QFile file(name);
        if (add_doc(&file, name) < 0)
        {
            emit s_error(++count_err);
            continue;

        }
        if (set_arr(&arr, l_doc, name) < 0)
        {
            emit s_error(++count_err);
            continue;
        }
        emit  s_status(++count_suc);
    }
}

int DomParser::add_doc(QIODevice *device, QString name)
{
    QDomDocument    doc;
    QString         errorStr;
    int             errorLine;
    int             errorColumn;

    if (!doc.setContent(device, true, &errorStr, &errorLine, &errorColumn))
    {
       emit  s_error_list("In file " + name + "   "  + "Line " +
                                  QString::number(errorLine) +
                                  ", Column " +
                                  QString::number(errorColumn) +
                                  ": " + errorStr + "\n");
        return (-1);
    }
    DomParser::l_doc = doc;
    return 1;
}

int DomParser::set_arr(List *arr,
                        QDomDocument doc, QString name)
{
    QMap<QString, QString>  l_map;
    QDomElement             root;
    QDomNode                node;

    root = doc.documentElement();
    if (root.tagName() != "root")
    {
        emit  s_error_list("In file " + name + "   :"  + "Not found root tag");
        return (-1);
    }
    node = root.firstChild();
    while (!node.isNull())
    {
        QString text;
        QString tag;
        QDomNode ch_node;

        tag = node.toElement().tagName();
        ch_node = node.firstChild();
        if (ch_node.nodeType() == QDomNode::TextNode)
            text = ch_node.toText().data();
        l_map.insert(tag,text);
        node = node.nextSibling();
    }
    arr->append(l_map);
    return (1);
}

