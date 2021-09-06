#ifndef MESSAGE_H
#define MESSAGE_H

#include<qjsondocument.h>
#include<qjsonarray.h>
#include<qjsonobject.h>
#include<qjsonvalue.h>
#include<vector>
#include <QDebug>
#include "Menu.h"
enum ServerAction{
    MENU_SEND, //发送菜单
    SERVER_DISHES, //上菜
    ORDER_SEND, //发送订单的
};

enum ClientAction{
    ADD_DISHES, //加菜
    SUB_DISHES, //退菜
    BUSY_DISHES, // 催菜
    REQUEST_MENU, //请求菜单
    REQUEST_ORDER, //请求订单
    ADD_COMMENT, //添加备注
};

class Message
{
public:
    Message();
    virtual QByteArray toJsonData() = 0;
    virtual void praseJson(QByteArray data) = 0;
    void addDishes(Dish dish);
    int getDishesCount();
    std::vector<Dish> getDishes();
protected:
    std::vector<Dish> dishes;
};

class MessageFromServer:public Message{
public:
    QByteArray toJsonData();
    void praseJson(QByteArray data);
    void setAction(ServerAction action);
    ServerAction getAction();
private:
    ServerAction action;
};

class MessageFromClient:public Message{
public:
    QByteArray toJsonData();
    void setAction(ClientAction action);
    void praseJson(QByteArray data);
    ClientAction getAction();
    int getTableId();
    void setTableId(int tableId);
private:
    ClientAction action;
    int tableID;
};

#endif // MESSAGE_H
