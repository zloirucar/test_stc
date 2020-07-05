#include "exportfile.h"

ExportFile::ExportFile(int col_count, QTableView *table)
{
    l_count = col_count;
    l_table = table;
}

void ExportFile::write_code()
{
    QFile file(QDir::currentPath() + "\\export.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("root");
    set_tag(&xmlWriter);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

void ExportFile::set_tag(QXmlStreamWriter *document)
{
    int row = l_table->selectionModel()->currentIndex().row();
    while (l_count != 0)
    {
        QString chr = l_table->model()->index(row, l_count - 1).data().toString();
        QString tag = l_table->model()->headerData(l_count - 1, Qt::Horizontal).toString();
        document->writeStartElement(tag);
        document->writeCharacters(chr);
        document->writeEndElement();
        l_count--;
    }
}
