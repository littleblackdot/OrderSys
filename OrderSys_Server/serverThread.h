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
    void addDishTask(MessageFromClient mess);
    void subDishTask(MessageFromClient mess);
    void busyDishTask(MessageFromClient mess);
    void requestMenuTask(MessageFromClient mess);
    void requestOrderTask(MessageFromClient mess);
    void sendMessToClient(MessageFromServer mess);
    void addCommentTask(MessageFromClient mess);
    QByteArray  intToByte(int i);
    int bytesToInt(QByteArray bytes);
signals:
    void tableIdReport(int tableId, QTcpSocket* socket);
    void requestReport(int tableId);
private:
    QTcpSocket *socket;

    DBHelper helper;
};

#endif // SERVERTHREAD_H
