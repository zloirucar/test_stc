#include "table_creator.h"

Table_Creator::Table_Creator()
{

}

int Table_Creator::find_vert(QString key, QStringList vert)
{
    QListIterator<QString> list_iter(vert);

    int i = 0;
    list_iter.toFront();
    while (list_iter.hasNext())
    {
        if (key == list_iter.next())
            return i;
        i++;
    }
    if (!list_iter.hasNext())
        return -1;
}


QStandardItemModel  *Table_Creator::init_table(QList<QMap<QString, QString>> arr)
{
    QStandardItemModel  *model = new QStandardItemModel;
    QStandardItem       *item;
    int                 i = 1;

    //Заголовки столбцов
    QStringList horizontalHeader;
    QStringList verticalHeader;
    QListIterator<QMap<QString, QString>> iter(arr);
    iter.toFront();
    while(iter.hasNext())
    {
        verticalHeader.prepend(QString::number(i));
        QMapIterator<QString, QString> m_iter(iter.next());
        m_iter.toFront();
        if (horizontalHeader.isEmpty())
        {
            while(m_iter.hasNext())
            {
                m_iter.next();
                horizontalHeader.append(m_iter.key());
                item = new QStandardItem(QString(m_iter.value()));
                model->setItem(i - 1, find_vert(m_iter.key(), horizontalHeader) ,item);
            }
        } else
        {

        }
        i++;
    }
    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);
    return model;
}

