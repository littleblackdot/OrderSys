#ifndef USER_H
#define USER_H

#include<QString>

typedef enum UserType{
    Manager, Cashier, Chef
}UserType;

class User
{
public:
    User();
    User(int id, UserType type, QString name);
    void setUserType(const UserType &value);

    UserType getUserType() const;

    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);

private:
    int id;
    UserType userType;
    QString name;
};

#endif // USER_H
