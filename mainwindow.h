#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QThread>
#include "generalparse.h"
#include "exportfile.h"
#include "db_work.h"
#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void change_table();
    ~MainWindow();

private slots:
    void on_pushButton_clicked(); //Кнопка импорта
    void slotCustomMenu(QPoint pos);
    void slotDelete();
    void slotEdit();
    void slotExport();
    void on_pushButton_2_clicked(); //Кнопка очистки
    void create_table();
    void edit_db();
private:
    Ui::MainWindow *ui;
    ImportDialog *status = nullptr;
    db_work *db;
    TableModel *my_model; // модель, по которой строится TableView
    int col_count;
};

#endif // MAINWINDOW_H
