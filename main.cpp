#include "mainwindow.h"
#include <QApplication>
#include <domparser.h>
#include <table_creator.h>
#include <QFile>


QStandardItemModel  *parseFile(const QString &fileName) {
    QTableView *view = new QTableView;
    QFile file(fileName);
    if (!file.exists())
    {
        printf("File not found");
        exit(1);
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        printf("Ошибка открытия для чтения\n");
        exit(1);
    }
    DomParser *pars = new DomParser(&file, view);
    pars->test(&(pars->arr), pars->l_doc);
    Table_Creator *model = new Table_Creator();
    return(model->init_table(pars->arr));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.set_model( parseFile(
                     "C:\\Users\\Ivan\\Documents\\XML_Reader\\TestFolder\\atom.xml"));
    w.show();
    return a.exec();
}
