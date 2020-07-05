#include "generalparse.h"

GeneralParse::GeneralParse(QString str)
{
  l_str = str;
}

void GeneralParse::doParse()
{
    File_Reader files(GeneralParse::l_str);
    DomParser pars;
    connect (&files, SIGNAL(s_error(int)), this, SLOT(reader_error(int)));
    connect(&files, SIGNAL(s_status(int)), this, SLOT(reader_status(int)));
    connect(&files, SIGNAL(s_error_list(QString)), this, SLOT(error_list(QString)));
    connect(&pars, SIGNAL(s_error(int)), this, SLOT(parse_error(int)));
    connect(&pars, SIGNAL(s_status(int)), this, SLOT(parse_open(int)));
    connect(&pars, SIGNAL(s_error_list(QString)), this, SLOT(error_list(QString)));
    files.get_files(GeneralParse::l_str);
    pars.parse_files(files.find_files);
    arr = pars.arr;
    emit send_arr(arr);
    emit finished();
}

void GeneralParse::reader_error(int count)
{
    emit send_to_open_error(count);
}

void GeneralParse::reader_status(int count)
{
    emit send_to_open_status(count);
}

void GeneralParse::parse_error(int count)
{
    emit send_to_parse_error(count);
}

void GeneralParse::parse_open(int count)
{
    emit send_to_parse_status(count);
}

void GeneralParse::error_list(QString message)
{
    emit send_to_error_list(message);
}
