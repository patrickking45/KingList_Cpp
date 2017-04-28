#include "services_permission.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <iostream>
#include <QVariantMap>
#include "model_permission.h"

using namespace std;


void PermissionServices::replyFinishedgetPermissions(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
     QJsonArray json_array = jsonResponse.array();

        foreach (const QJsonValue &value, json_array) {
                QJsonObject perm = value.toObject();
                Permission* p = new Permission();
                p = mapperPermission(perm);
                this->listPermissions.push_back(p);
            }
        emit mapFinished();
}
void PermissionServices::replyFinishedeletePermission(QNetworkReply *reply)
{
    qDebug()<<"Reply of delete Permission: "<<QString(reply->readAll());
}
void PermissionServices::replyFinishedcreatePermission(QNetworkReply *reply)
{
    qDebug()<<"Reply of create Permission: "<<QString(reply->readAll());
}
void PermissionServices::replyFinishedupdatePermission(QNetworkReply *reply)
{
    qDebug()<<"Reply of update Permission: "<<QString(reply->readAll());
}
vector<Permission*> PermissionServices::getPermissions()
{
    this->listPermissions.clear();
        QUrl qrl(this->pref.baseUrl + this->baseUrlPermission);
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetPermissions(QNetworkReply*)));
        QNetworkRequest request(qrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept-Language", "en-US;q=1.0");
        manager->get(request);
        QEventLoop loop;
        connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
        loop.exec();
        return this->listPermissions;
}

void PermissionServices::createPermission(Permission* perm)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlPermission);
    QNetworkRequest request(qrl);
    manager = new QNetworkAccessManager(this);
    QJsonObject json_obj_permission = mapperPermissionToJsonObject(perm);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    QJsonDocument doc(json_obj_permission);
    manager->post(request, doc.toJson(QJsonDocument::Compact));
     connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedcreatePermission(QNetworkReply*)));
}
void PermissionServices::updatePermission(Permission* perm)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlPermission+QString::number(perm->listID)+"/"+QString::number(perm->userID));
    manager = new QNetworkAccessManager(this);
    QJsonObject json_obj_permission = mapperPermissionToJsonObject(perm);
    qDebug()<< json_obj_permission;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedupdatePermission(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    QJsonDocument doc(json_obj_permission);
    QByteArray bytes = doc.toJson();
    manager->put(request,bytes);
}
void PermissionServices::deletePermission(Permission* perm)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlPermission+QString::number(perm->listID)+"/"+QString::number(perm->userID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedeletePermission(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->deleteResource(request);
}
inline Permission* PermissionServices::mapperPermission(QJsonObject json_obj_perm)
{
    Permission* p = new Permission();
    int _listID = json_obj_perm["permissionPK"].toObject()["listid"].toInt();
    int _userID = json_obj_perm["permissionPK"].toObject()["userid"].toInt();
    QString permid = QString(QString::number(_listID) +QString::number(_userID));
    p->permID = permid.toInt();
    p->listID = _listID;
    p->userID = _userID;
    p->canCheck = json_obj_perm["cancheck"].toBool();
    p->canDelete = json_obj_perm["candelete"].toBool();
    p->canShare = json_obj_perm["canshare"].toBool();
    p->canWrite = json_obj_perm["canwrite"].toBool();
    return p;
}
inline QJsonObject PermissionServices::mapperPermissionToJsonObject(Permission* perm)
{
    QJsonObject json_obj_permission;
    User* u = userServ.getUserByID(perm->userID);
    QJsonObject json_obj_user = userServ.mapperUserToJsonObject(u,true);
    QJsonObject json_obj_pk;

    json_obj_permission.insert("cancheck",perm->canCheck);
    json_obj_permission.insert("candelete",perm->canDelete);
    json_obj_permission.insert("canshare",perm->canShare);
    json_obj_permission.insert("canwrite",perm->canWrite);

    json_obj_pk.insert("listid",perm->listID);
    json_obj_pk.insert("userid",perm->userID);

    json_obj_permission.insert("permissionPK",json_obj_pk);
    json_obj_permission.insert("utilisateur",json_obj_user);
    return json_obj_permission;

}
