#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>

class ImportDialog:public QWidget
{
    Q_OBJECT
public:
    ImportDialog();
    void add_to_parse_status(int count);
    void add_to_error_list(QString message);
    void add_to_open_error(int count);
    void add_to_parse_error(int count);
    void add_to_open_status(int count);
    QLabel *open_status;
private:
    int count_parse_error;
    int count_open_error;
    int count_open_status;
    int count_parse_status;
    QString error_list;
    QLabel *open_errors;
    QLabel *parse_errors;
    QLabel *parse_status;
    QLabel *error_messages;
    QPushButton *ok_button;
    QGridLayout *grid_layout;
};

#endif // IMPORTDIALOG_H
