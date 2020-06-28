#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table_creator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::set_model(QStandardItemModel *model)
{
    MainWindow::l_model = model;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ui->tableView->setModel(l_model);
}
