#ifndef MENU_H
#define MENU_H

#include<QString>
#include<qjsondocument.h>
#include<qjsonarray.h>
#include<qjsonobject.h>
#include<qjsonvalue.h>


enum DishStatus{
    PUTAWAY, //上架中
    SOLDOUT  //下架
};

struct Dish{
    int id;
    QString name;
    double price;
    QString comment; //备注
    QJsonObject toJsonObject(){
        QJsonObject obj;
        obj.insert("id", id);
        obj.insert("name", name);
        obj.insert("price", price);
        obj.insert("comment", comment);
        return obj;
    }
    void parseJsonObject(QJsonObject obj){
        if(obj.contains("id")){
            QJsonValue idValue = obj.take("id");
            if(idValue.isDouble()){
                id = idValue.toInt();
            }
        }
        if(obj.contains("name")){
            QJsonValue nameValue = obj.take("name");
            if(nameValue.isString()){
                name = nameValue.toString();
            }
        }
        if(obj.contains("price")){
            QJsonValue priceValue = obj.take("price");
            if(priceValue.isDouble()){
                price = priceValue.toDouble();
            }
        }
        if(obj.contains("comment")){
            QJsonValue commentValue = obj.take("comment");
            if(commentValue.isString()){
                comment = commentValue.toString();
            }
        }
    }
};

#endif // MENU_H
