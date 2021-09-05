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

void server_tcp::addSocket(QTcpSocket *socket)
{
    socketDeque.push_back(socket);
}

server_tcp::~server_tcp()
{
    while(socketDeque.size() > 0){
        QTcpSocket *socket = socketDeque.back();
        socketDeque.pop_back();
        socket->close();
    }
    server->close();
}
