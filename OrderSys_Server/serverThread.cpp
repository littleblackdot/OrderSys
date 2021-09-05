#include "serverThread.h"

ServerThread::ServerThread(QTcpSocket *socket): socket(socket)
{

}

void ServerThread::run()
{

    connect(socket, &QTcpSocket::readyRead,
            [&](){
                QByteArray array1 = socket->read(4);
                int len = bytesToInt(array1);
                QByteArray array2 = socket->read(len);
                MessageFromClient mess;
                mess.praseJson(array2);
                switch(mess.getAction()){
                    case REQUEST_MENU:{
                            qDebug() << "case request_menu" << endl;
                            requestMenuTask(mess.getTableId());
                            break;
                        }
                    case REQUEST_ORDER:{
                            qDebug() << "case request_order" << endl;
                            requestOrderTask(mess.getTableId());
                            break;
                        }
                    default: break;
                }
            });
}

void ServerThread::addDishTask(int tableId)
{

    emit getRequest();
}

void ServerThread::sudDishTask(int tableId)
{
    emit getRequest();
}

void ServerThread::busyDishTask(int tableId)
{
    emit getRequest();
}

void ServerThread::requestMenuTask(int tableId)
{
     QSqlQuery query(helper.getDB());
     QString sql = QString("select * from menu where status = 0");
     MessageFromServer mess;
     mess.setAction(MENU_SEND);
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
         mess.addDishes(dish);
     }
     QByteArray json = mess.toJsonData();
     socket->write(json);
     //emit getRequest();
}

void ServerThread::requestOrderTask(int tableId)
{
    QSqlQuery query(helper.getDB());
     QSqlQuery query2(helper.getDB());
    QString sql = QString("select * from orders where tableId = %1").arg(tableId);
    MessageFromServer mess;
    mess.setAction(ORDER_SEND);
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
        if(query.next()){
            dish.name = query.value(1).toString();
            dish.price = query.value(2).toDouble();
        }
        mess.addDishes(dish);
    }
    if(mess.getDishesCount() == 0){
        //return ;
    }
    QByteArray json = mess.toJsonData();
    socket->write(json);
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


