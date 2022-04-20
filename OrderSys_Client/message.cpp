#include "message.h"

Message::Message()
{

}

void Message::addDishes(Dish dish)
{
    dishes.push_back(dish);
}

int Message::getDishesCount()
{
    return dishes.size();
}

std::vector<Dish> Message::getDishes()
{
    return dishes;
}

QByteArray MessageFromServer::toJsonData(){
    QJsonObject mess;
    QJsonArray dishArray;
    for(int i=0; i<dishes.size(); ++i){
        QJsonObject item = dishes[i].toJsonObject();
        dishArray.insert(i, item);
    }
    mess.insert("action", action);
    mess.insert("dishArray", dishArray);
    QJsonDocument doc(mess);
    return doc.toJson(); // 可选参数QJsonDocument::Compact生成紧凑型格式的json
}

void MessageFromServer::praseJson(QByteArray data){
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error == QJsonParseError::NoError){
        if(doc.isObject()){
            QJsonObject obj = doc.object();
            if(obj.contains("action")){
                QJsonValue action_j = obj.take("action");
                if(action_j.isDouble()){
                    action = (ServerAction)action_j.toVariant().toInt();
                }
            }

            if(obj.contains("dishArray")){
                QJsonValue arrayValue = obj.take("dishArray");
                if(arrayValue.isArray()){
                    QJsonArray arr = arrayValue.toArray();
                    for(int i=0; i<arr.size(); ++i){
                        QJsonValue itemValue = arr.at(i);
                        Dish dish;
                        if(itemValue.isObject()){
                            dish.parseJsonObject(itemValue.toObject());
                            dishes.push_back(dish);
                        }
                    }

                }
            }
        }
    }else{
        qDebug()<< "in MessageFeomServer::parseJson json err";
    }
}

void MessageFromServer::setAction(ServerAction action)
{
    this->action = action;
}

ServerAction MessageFromServer::getAction()
{
    return action;
}

QByteArray MessageFromClient::toJsonData(){
    QJsonObject mess;
    QJsonArray dishArray;
    for(int i=0; i<dishes.size(); ++i){
        QJsonObject item = dishes[i].toJsonObject();
        dishArray.insert(i, item);
    }
    mess.insert("action", action);
    mess.insert("dishArray", dishArray);
    mess.insert("tableID", tableID);
    QJsonDocument doc(mess);
    return doc.toJson(); // 可选参数:QJsonDocument::Compact生成紧凑型格式的json
}

void MessageFromClient::setAction(ClientAction action)
{
    this->action = action;
}

void MessageFromClient::praseJson(QByteArray data){
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error == QJsonParseError::NoError){
        if(doc.isObject()){
            QJsonObject obj = doc.object();
            if(obj.contains("action")){
                QJsonValue action_j = obj.take("action");
                if(action_j.isDouble()){
                    action = (ClientAction)action_j.toVariant().toInt();
                }
            }

            if(obj.contains("tableID")){
                QJsonValue tableID_j = obj.take("tableID");
                if(tableID_j.isDouble()){
                    tableID = tableID_j.toVariant().toInt();
                }
            }

            if(obj.contains("dishArray")){
                QJsonValue arrayValue = obj.take("dishArray");
                if(arrayValue.isArray()){
                    QJsonArray arr = arrayValue.toArray();
                    for(int i=0; i<arr.size(); ++i){
                        QJsonValue itemValue = arr.at(i);
                        Dish dish;
                        if(itemValue.isObject()){
                            dish.parseJsonObject(itemValue.toObject());
                            dishes.push_back(dish);
                        }
                    }

                }
            }
        }
    }else{
        qDebug()<< "in MessageFeomServer::parseJson json err";
    }
}

ClientAction MessageFromClient::getAction()
{
    return action;
}

int MessageFromClient::getTableId()
{
    return tableID;
}

void MessageFromClient:: setTableId(int tableId){
    this->tableID = tableId;
}
