#include "domparser.h"

DomParser::DomParser(QIODevice *device, QTableView *view)
{
    QDomDocument    doc;
    QString         errorStr;
    int             errorLine;
    int             errorColumn;

    if (!doc.setContent(device, true, &errorStr, &errorLine, &errorColumn))
    {
        qWarning("Line %d, column %d: %s",
                 errorLine, errorColumn, errorStr.toStdString());
        return;
    }
    DomParser::l_doc = doc;
}

void DomParser::test(QList<QMap<QString, QString>> *arr, QDomDocument l_doc)
{
    set_arr(arr, l_doc);
}

void DomParser::set_arr(QList<QMap<QString, QString>> *arr,
                        QDomDocument doc)
{
    QMap<QString, QString>  l_map;
    QDomElement             root;
    QDomNode                node;

    root = doc.documentElement();
    if (root.tagName() != "root")
    {
        qWarning("Not found root tag");
        return;
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
}

