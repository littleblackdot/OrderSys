#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


class DBHelper
{
public:
    DBHelper();
    QSqlDatabase getDB();
    ~DBHelper();
private:
    QSqlDatabase db;
};

#endif // DBHELPER_H
