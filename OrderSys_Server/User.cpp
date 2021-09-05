#include "User.h"

User::User()
{

}

User::User(int id, UserType type, QString name):id(id), userType(type), name(name)
{

}

void User::setUserType(const UserType &value)
{
    userType = value;
}

UserType User::getUserType() const
{
    return userType;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &value)
{
    name = value;
}

int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    id = value;
}
