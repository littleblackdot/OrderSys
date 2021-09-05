#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMessageBox>
#include "DBHelper.h"
#include "message.h"
#include "Menu.h"


class ServerThread:public QThread
{
    Q_OBJECT
public:
    ServerThread(QTcpSocket *socket);
    void run();
    void addDishTask(int tableId);
    void sudDishTask(int tableId);
    void busyDishTask(int tableId);
    void requestMenuTask(int tableId);
    void requestOrderTask(int tableId);
    QByteArray  intToByte(int i);
    int bytesToInt(QByteArray bytes);
signals:
    void getRequest();
private:
    QTcpSocket *socket;
    DBHelper helper;
};

#endif // SERVERTHREAD_H
