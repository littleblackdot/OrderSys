#include "server_tcp.h"

server_tcp::server_tcp(QWidget *parent):QWidget(parent)
{
    server = new QTcpServer();
    server->listen(QHostAddress::Any, SERVER_PORT);
}

QTcpServer *server_tcp::getServer()
{
    return server;
}

void server_tcp::addSocket(int tableId, QTcpSocket *socket)
{
    socketMap.insert(std::make_pair(tableId, socket));
}

std::multimap<int, QTcpSocket *> server_tcp::getSocketMap()
{
    return socketMap;
}

server_tcp::~server_tcp()
{
    if(socketMap.size() > 0){
       for(auto i = socketMap.begin(); i != socketMap.end(); ++i){
           i->second->close();
       }
    }
    server->close();
}
