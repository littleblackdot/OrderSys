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
    std::lock_guard<std::mutex> guardMutex(mutex_map);
    socketMap.insert(std::make_pair(tableId, socket));
}

std::multimap<int, QTcpSocket *> server_tcp::getSocketMap()
{
    return socketMap;
}

void server_tcp::removeSocket(QTcpSocket *socket, int tableid)
{
    std::lock_guard<std::mutex> guardMutex(mutex_map);
    auto range = socketMap.equal_range(tableid);
    for(auto i=range.first; i!=range.second; i++){
        if(i->second == socket){
            socketMap.erase(i);
            break;
        }
    }
}

std::vector<QTcpSocket *> server_tcp::findSockets(int tableid)
{
    std::lock_guard<std::mutex> guardMutex(mutex_map);
    std::vector<QTcpSocket*> res;
    auto range = socketMap.equal_range(tableid);
    for(auto i=range.first; i!=range.second; i++){
        res.push_back(i->second);
    }
    return res;
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
