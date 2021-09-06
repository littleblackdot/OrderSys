#ifndef SERVER_TCP_H
#define SERVER_TCP_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <map>
#include "serverThread.h"

#define SERVER_PORT 11245

class server_tcp:public QWidget
{
    Q_OBJECT
public:
    server_tcp(QWidget *parent = nullptr);
    QTcpServer* getServer();
    void addSocket(int tableId, QTcpSocket* socket);
    std::multimap<int, QTcpSocket*> getSocketMap();
    ~server_tcp();
private:
    QTcpServer *server;
    std::multimap<int, QTcpSocket*> socketMap;
};

#endif // SERVER_TCP_H
