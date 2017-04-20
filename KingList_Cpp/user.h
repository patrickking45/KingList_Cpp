#ifndef USER_H
#define USER_H
#include <QString>
class User
{
private:
    int userID;
    QString login;
    QString password;
    QString name;
public:
    User(){};
    User(int,QString,QString,QString);
    User(QString,QString,QString);
};


User::User(int _userID,QString _login,QString _password,QString _name)
{
    this->userID = _userID;
    this->login = _login;
    this->password = _password;
    this->name = _name;
}
User::User(QString _login,QString _password,QString _name)
{
    this->login = _login;
    this->password = _password;
    this->name = _name;
}



#endif // USER_H
