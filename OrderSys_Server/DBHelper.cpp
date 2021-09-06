#include "DBHelper.h"

DBHelper::DBHelper()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    db.setHostName("192.168.124.131");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("Root.999");
    db.setDatabaseName("order_sys");
    if(!db.open()){
        qDebug() << "数据库连接失败";
    }
}

QSqlDatabase DBHelper::getDB()
{
    return db;
}

DBHelper::~DBHelper()
{
    db.close();
}

