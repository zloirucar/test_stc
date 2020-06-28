#include "domparser.h"

DomParser::DomParser()
{

}

void DomParser::parse_files(const QStringList file_names)
{
    QStringListIterator iter(file_names);
    iter.toFront();
    while(iter.hasNext())
    {
        QFile file(iter.next());
        if (add_doc(&file) < 0)
            continue;
        set_arr(&(DomParser::arr), DomParser::l_doc);
    }
}

int DomParser::add_doc(QIODevice *device)
{
    QDomDocument    doc;
    QString         errorStr;
    int             errorLine;
    int             errorColumn;

    if (!doc.setContent(device, true, &errorStr, &errorLine, &errorColumn))
    {
        qWarning("Line %d, column %d: %s",
                 errorLine, errorColumn, errorStr.toStdString());
        return -1;
    }
    DomParser::l_doc = doc;
    return 1;
}

void DomParser::set_arr(List *arr,
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

