#include "importdialog.h"


ImportDialog::ImportDialog() : QWidget()
{
    open_status = new QLabel("Success open: 0");
    open_errors = new QLabel("Error open: 0");
    parse_errors = new QLabel("Error parse: 0");
    parse_status = new QLabel("Success parse: 0");
    error_messages = new QLabel("");
    ok_button = new QPushButton("Ok");

    connect(ok_button, SIGNAL(clicked(bool)), this, SLOT(close()));
    grid_layout = new QGridLayout;
    grid_layout->addWidget(open_status, 0, 0);
    grid_layout->addWidget(open_errors, 0, 1);
    grid_layout->addWidget(parse_status, 1, 0);
    grid_layout->addWidget(parse_errors, 1, 1);
    grid_layout->addWidget(error_messages, 2,0);
    grid_layout->addWidget(ok_button, 3, 2);
    setLayout(grid_layout);
}

void ImportDialog::add_to_open_status(int count)
{
    open_status->setText("Success open: " + QString::number(count));
}

void ImportDialog::add_to_parse_status(int count)
{
    parse_status->setText("Success parse: " + QString::number(count));
}

void ImportDialog::add_to_error_list(QString message)
{
    error_messages->setText(error_messages->text() + message);
}

void ImportDialog::add_to_open_error(int count)
{
    open_errors->setText("Error open: " + QString::number(count));
}

void ImportDialog::add_to_parse_error(int count)
{
    parse_errors->setText("Error parse: " + QString::number(count));
}
