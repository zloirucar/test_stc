#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>


//DEBUG
#include <QThread>

typedef QList<QMap<QString, QString>> List;

class ImportDialog:public QWidget
{
    Q_OBJECT
public:
    ImportDialog();
    List get_arr();
    ~ImportDialog();

private:
    int count_parse_error;
    int count_open_error;
    int count_open_status;
    int count_parse_status;
    QString error_list;
    QLabel *open_errors;
    QLabel *open_status;
    QLabel *parse_errors;
    QLabel *parse_status;
    QLabel *error_messages;
    QPushButton *ok_button;
    QGridLayout *grid_layout;
    List arr;
public slots:
    //Слоты для принятия сигнала из потока парсера
    void add_to_parse_status(int count);
    void add_to_error_list(QString message);
    void add_to_open_error(int count);
    void add_to_parse_error(int count);
    void add_to_open_status(int count);
    void add_list(List done_arr);

signals:
    void list_done();
};

Q_DECLARE_METATYPE(List)
#endif // IMPORTDIALOG_H
