#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table_creator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenu(QPoint)));
}

void MainWindow::set_model(QStandardItemModel *model)
{
    MainWindow::l_model = model;
}

void MainWindow::slotCustomMenu(QPoint pos)
{
    QMenu *menu = new QMenu(this);
  //  QAction *edit = new QAction(QString("Edit"), this);
    QAction *del = new QAction(QString("Delete"), this);
   // connect(edit, SIGNAL(triggered()), this, SLOT(slotEdit()));
    connect(del, SIGNAL(triggered()), this, SLOT(slotDelete()));
 //   menu->addAction(editDevice);
    menu->addAction(del);
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::slotDelete()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    MainWindow::l_model->removeRow(row);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ui->tableView->setModel(l_model);
}

void MainWindow::on_pushButton_2_clicked()
{
     QStandardItemModel model;
     ui->tableView->setModel(&model);
}
