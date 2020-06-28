#include "mainwindow.h"
#include <QApplication>
#include <domparser.h>
#include <table_creator.h>
#include "file_reader.h"
#include <QFile>
#include <QDir>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    File_Reader files ("C:\\Users\\Ivan\\Documents\\XML_Reader\\TestFolder\\");
    DomParser pars;
    pars.parse_files(files.find_files);
    Table_Creator model;
    w.set_model(model.init_table(pars.arr));
    w.show();
    return a.exec();
}
