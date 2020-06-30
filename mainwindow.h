#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "domparser.h"
#include "QStandardItemModel"
#include "domparser.h"
#include "table_creator.h"
#include "file_reader.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "importdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void set_model(QStandardItemModel *model);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void slotCustomMenu(QPoint pos);
    void slotDelete();
    void slotEdit();
    void on_pushButton_2_clicked();
private:
    Ui::MainWindow *ui;
    QStandardItemModel *l_model;
};

#endif // MAINWINDOW_H
