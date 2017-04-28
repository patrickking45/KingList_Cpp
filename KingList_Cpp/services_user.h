#ifndef NET_H
#define NET_H
#include <QObject>
#include <QtCore>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <vector>
#include "model_user.h"
#include "model_item.h"
#include "util_preferences.h"
#include <QMetaType>
#include <QJsonObject>


class UserServices : public QObject
{
Q_OBJECT
  QNetworkAccessManager *manager;
public:
  std::vector<User*> listUsers;
  User* user;
  PREFERENCES pref;
  QString baseUrlUser = QString("model.utilisateur/");


signals:
    void mapFinished();

private slots:
  void replyFinishedgetUsers(QNetworkReply *);
  void replyFinishedgetUserByID(QNetworkReply *);
  void replyFinisheddeleteUserByID(QNetworkReply *);
  void replyFinishedcreateUser(QNetworkReply *);
  void replyFinishedupdateUser(QNetworkReply *);
public:
  vector<User*> getUsers();
  User* getUserByID(int);
  void deleteUserByID(int);
  void createUser(User*);
  void updateUser(User*);

  User* mapperUser(QJsonObject);
  QJsonObject mapperUserToJsonObject(User*,bool);
};



#endif // NET_H
