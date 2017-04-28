#ifndef USER_H
#define USER_H
#include <QString>

using namespace std;

class User
{
public:
    int userID;
    QString login;
    QString password;
    QString name;

    User(){}
    User(int,QString,QString,QString);
    User(QString,QString,QString);

    QString getLogin();
    QString getPassword();
    QString getName();
};


inline User::User(int _userID,QString _login,QString _password,QString _name)
{
    this->userID = _userID;
    this->login = _login;
    this->password = _password;
    this->name = _name;
}
inline User::User(QString _login,QString _password,QString _name)
{
    this->login = _login;
    this->password = _password;
    this->name = _name;
}

inline QString User::getLogin(){
    return this->login;
}

inline QString User::getPassword(){
    return this->password;
}

inline QString User::getName(){
    return this->name;
}


#endif // USER_H
