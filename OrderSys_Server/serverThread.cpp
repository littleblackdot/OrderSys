#include "serverThread.h"

ServerThread::ServerThread(QTcpSocket *socket): socket(socket)
{

}

void ServerThread::run()
{
    connect(socket, &QTcpSocket::readyRead,
            [&](){
                while(socket->bytesAvailable() >0 ){
                    QByteArray array1 = socket->read(4);
                    int len = bytesToInt(array1);
                    QByteArray array2 = socket->read(len);
                    MessageFromClient mess;
                    mess.praseJson(array2);
                    switch(mess.getAction()){
                        case REQUEST_MENU:{
                                qDebug() << "case request_menu" << endl;
                                requestMenuTask(mess);
                                break;
                            }
                        case REQUEST_ORDER:{
                                qDebug() << "case request_order" << endl;
                                requestOrderTask(mess);
                                break;
                            }
                        case ADD_DISHES:{
                                qDebug() << "case add_dishes" << endl;
                                addDishTask(mess);
                                break;
                            }
                        case SUB_DISHES:{
                                qDebug() << "case sub_dishes" << endl;
                                subDishTask(mess);
                                break;
                            }
                        case BUSY_DISHES:{
                                qDebug() << "case busy_dishes" << endl;
                                busyDishTask(mess);
                                break;
                            }
                        case ADD_COMMENT:{
                                qDebug() << "case add_comment" << endl;
                                addCommentTask(mess);
                                break;
                            }
                        default: break;
                    }
                }
            });
}

void ServerThread::addDishTask(MessageFromClient mess)
{
    //加菜
    int tableId = mess.getTableId();
    std::vector<Dish> dishes = mess.getDishes();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    if(dishes.size() > 0){
        QString sql = QString("insert into orders values(NULL, %1, %2, 0, '')").arg(tableId).arg(dishes[0].id);
        bool ret = query.exec(sql);
        if(!ret){
            QSqlError err = query.lastError();   //得到最近一次的错误信息
            QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
            qDebug()<< str << endl;
        }
    }
    emit requestReport(tableId);
}

void ServerThread::subDishTask(MessageFromClient mess)
{
    //退菜
    Dish dish = mess.getDishes().at(0);
    int tableId = mess.getTableId();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    int orderId;
    QString sql = QString("select id from orders where tableID = %1 and dishID = %2 limit 1").arg(tableId).arg(dish.id);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    if(query.next()){
        orderId = query.value(0).toInt();
    }
    QString sql2  = QString("delete from orders where id = %1").arg(orderId);
    ret = query.exec(sql2);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }

    emit requestReport(tableId);
}

void ServerThread::busyDishTask(MessageFromClient mess)
{
    //催菜
    Dish dish = mess.getDishes().at(0);
    int tableId = mess.getTableId();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql  = QString("update orders set status = 2 where tableID = %1 and dishID = %2")
                    .arg(tableId)
                    .arg(dish.id);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    emit requestReport(tableId);
}

void ServerThread::requestMenuTask(MessageFromClient mess)
{
     QSqlQuery query(helper.getDB());
     QString sql = QString("select * from menu where status = 0");
     MessageFromServer messToC;
     messToC.setAction(MENU_SEND);
     bool ret = query.exec(sql);
     if(!ret){
         QSqlError err = query.lastError();   //得到最近一次的错误信息
         QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
         qDebug()<< str << endl;
     }
     while(query.next()){
         Dish dish;
         dish.id = query.value(0).toInt();
         dish.name = query.value(1).toString();
         dish.price = query.value(2).toDouble();
         messToC.addDishes(dish);
     }
     sendMessToClient(messToC);
     //emit getRequest();
}

void ServerThread::requestOrderTask(MessageFromClient mess)
{
    QSqlQuery query(helper.getDB());
    QSqlQuery query2(helper.getDB());
    QString sql = QString("select * from orders where tableID = %1").arg(mess.getTableId());
    MessageFromServer messToC;
    messToC.setAction(ORDER_SEND);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    while(query.next()){
        Dish dish;
        dish.id = query.value(2).toInt();
        sql = QString("select * from menu where id = %1").arg(dish.id);
        bool ret = query2.exec(sql);
        if(!ret){
            QSqlError err = query.lastError();   //得到最近一次的错误信息
            QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
            qDebug()<< str << endl;
        }
        if(query2.next()){
            dish.name = query2.value(1).toString();
            dish.price = query2.value(2).toDouble();
        }
        messToC.addDishes(dish);
    }
    sendMessToClient(messToC);
    emit tableIdReport(mess.getTableId(), socket);
}

QByteArray ServerThread:: intToByte(int i){
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & i);
    abyte0[1] = (uchar) ((0x0000ff00 & i) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & i) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & i) >> 24);
    return abyte0;
}

int ServerThread:: bytesToInt(QByteArray bytes){
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}

void ServerThread::sendMessToClient(MessageFromServer mess)
{
    QByteArray json = mess.toJsonData();
    json.push_front(intToByte(json.size()));
    socket->write(json, json.size());
}

void ServerThread::addCommentTask(MessageFromClient mess)
{
    Dish dish = mess.getDishes().at(0);
    int tableId = mess.getTableId();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql  = QString("update orders set comment = '%1' where tableID = %2 and dishID = %3")
                    .arg(dish.comment)
                    .arg(tableId)
                    .arg(dish.id);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug()<< str << endl;
    }
    emit requestReport(tableId);
}


