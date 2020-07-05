#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenu(QPoint)));
    ui->tableView->hide();
    MainWindow::db = new db_work;
    MainWindow::db->get_data(); // подгрузка данных из бд или создание нового файла БД
    MainWindow::my_model = new TableModel(db->get_arr(),db->get_map(), db->get_col(), db->get_row());
    ui->tableView->setModel(my_model);
    ui->tableView->show();

}

void MainWindow::change_table()
{
    List arr;
    arr = my_model->get_arr();
    MainWindow::db = new db_work(&(arr));
    QThread *th = new QThread;
    connect(th, SIGNAL(started()), db, SLOT(do_Work_ch()));
    connect(db, SIGNAL(finished()), th, SLOT(terminate()));
    MainWindow::db->moveToThread(th);
    th->start();
}

void MainWindow::slotCustomMenu(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    QAction *edit = new QAction(QString("Edit"), this);
    QAction *del = new QAction(QString("Delete"), this);
    QAction *exp = new QAction(QString("Export"), this);
    connect(edit, SIGNAL(triggered()), this, SLOT(slotEdit()));
    connect(del, SIGNAL(triggered()), this, SLOT(slotDelete()));
    connect(exp, SIGNAL(triggered(bool)), this, SLOT(slotExport()));
    menu->addAction(edit);
    menu->addAction(del);
    menu->addAction(exp);
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::slotDelete()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    MainWindow::my_model->removeRow(row);
    MainWindow::change_table();
}

void MainWindow::slotEdit()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    ui->tableView->edit(index);
}

void MainWindow::slotExport()
{
    ExportFile file(my_model->columnCount(QModelIndex()), ui->tableView);
    file.write_code();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (status == nullptr)
        status = new ImportDialog;
    else
    {
        status->destroyed();
        status = new ImportDialog;
    }
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
    GeneralParse *pars = new GeneralParse(str);
    QThread *th = new QThread;
    status->show();
    connect(th, SIGNAL(started()), pars, SLOT(doParse()));
    connect(pars, SIGNAL(finished()), th, SLOT(terminate()));
    connect(pars, SIGNAL(send_to_open_error(int)), status, SLOT(add_to_open_error(int)));
    connect(pars, SIGNAL(send_to_open_status(int)), status, SLOT(add_to_open_status(int)));
    connect(pars, SIGNAL(send_to_parse_error(int)), status, SLOT(add_to_parse_error(int)));
    connect(pars, SIGNAL(send_to_parse_status(int)), status, SLOT(add_to_parse_status(int)));
    connect(pars, SIGNAL(send_to_error_list(QString)), status, SLOT(add_to_error_list(QString)));
    qRegisterMetaType<List>(); // Нужен для опрделения типа лист для передачи через сигнал-слот
    connect(pars, SIGNAL(send_arr(List)), status, SLOT(add_list(List)));
    connect(status, SIGNAL(list_done()), this, SLOT(edit_db()));
    pars->moveToThread(th);
    th->start();
}

void MainWindow::on_pushButton_2_clicked()
{
     my_model = new TableModel();
     ui->tableView->setModel(my_model);
}

void MainWindow::create_table()
{
    my_model = new TableModel(db->get_arr(),db->get_map(), db->get_col(), db->get_row());
    ui->tableView->setModel(my_model);
    ui->tableView->repaint();
}

void MainWindow::edit_db()
{
    List arr;
    arr = status->get_arr();
    db = new db_work(&(arr));
    QThread *th = new QThread;
    connect(th, SIGNAL(started()), db, SLOT(do_Work()));
    connect(db, SIGNAL(finished()), th, SLOT(terminate()));
    connect(db, SIGNAL(db_done()), this, SLOT(create_table()));
    db->moveToThread(th);
    th->start();
}
