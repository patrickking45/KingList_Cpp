#include "services_user.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <iostream>
#include <QVariantMap>
#include "model_user.h"

using namespace std;



void UserServices::replyFinishedgetUsers(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonArray json_array = jsonResponse.array();

    foreach (const QJsonValue &value, json_array) {
            QJsonObject user = value.toObject();
            User* u = new User();
            u = mapperUser(user);
            this->listUsers.push_back(u);
        }
    emit mapFinished();
}
void UserServices::replyFinishedgetUserByID(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject user = jsonResponse.object();
    User* userPtr = new User();
    userPtr = mapperUser(user);
    this->user = userPtr;
    emit mapFinished();

}
void UserServices:: replyFinisheddeleteUserByID(QNetworkReply *reply)
{
    qDebug() << "Response of delete: "<< (QString)reply->readAll();
}
void UserServices::replyFinishedcreateUser(QNetworkReply *reply)
{
    qDebug() << "Response of create: "<< (QString)reply->readAll();
}
void UserServices::replyFinishedupdateUser(QNetworkReply *reply)
{
    qDebug() << "Response of update: "<< (QString)reply->readAll();
}

vector<User*> UserServices::getUsers()
{
    this->listUsers.clear();
    QUrl qrl(this->pref.baseUrl + this->baseUrlUser);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetUsers(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->get(request);
    QEventLoop loop;
    connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
    loop.exec();
    return this->listUsers;
}
User* UserServices::getUserByID(int _userID)
{
    this->user = new User();
    QUrl qrl(this->pref.baseUrl+this->baseUrlUser + QString::number(_userID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetUserByID(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->get(request);
    QEventLoop loop;
    connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
    loop.exec();
    return this->user;
}
void UserServices::deleteUserByID(int _userID)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlUser + QString::number(_userID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinisheddeleteUserByID(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->deleteResource(request);
}
void UserServices::createUser(User* u)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlUser);
    manager = new QNetworkAccessManager(this);
    QNetworkRequest request(qrl);
    QJsonObject json_obj = mapperUserToJsonObject(u,false);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    QJsonDocument doc(json_obj);
    manager->post(request, doc.toJson(QJsonDocument::Compact));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedcreateUser(QNetworkReply*)));
}
void UserServices::updateUser(User* u)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlUser + QString::number(u->userID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedupdateUser(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    QJsonObject json_obj = mapperUserToJsonObject(u,true);
    json_obj.insert("userid",u->userID);
    QJsonDocument doc(json_obj);
    QByteArray bytes = doc.toJson();
    manager->put(request,bytes);
}

inline User* UserServices::mapperUser(QJsonObject user)
{
    User* u = new User();
    u->login = user["login"].toString();
    u->userID = user["userid"].toInt();
    u->password = user["password"].toString();
    u->name = user["name"].toString();
  return u;
}
inline QJsonObject UserServices::mapperUserToJsonObject(User* u,bool userIDIn)
{
    QJsonObject json_obj;
    json_obj.insert("login", u->getLogin());
    json_obj.insert("name", u->getName());
    json_obj.insert("password", u->getPassword());
    if(userIDIn)
    {
        json_obj.insert("userid",u->userID);
    }
    return json_obj;
}


