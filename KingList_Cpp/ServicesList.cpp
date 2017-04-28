#include "services_list.h"
#include <QString>
#include <QDate>
#include "model_permission.h"
#include "model_item.h"



void ListServices::replyFinishedgetLists(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonArray json_array = jsonResponse.array();

        foreach (const QJsonValue &value, json_array) {
                QJsonObject list = value.toObject();
                List* liste = new List();
                liste = mapperList(list);
                this->listLists.push_back(liste);
            }
        emit mapFinished();

}
void ListServices::replyFinishedgetListByID(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject list = jsonResponse.object();
    this->list = mapperList(list);
    emit mapFinished();
}
void ListServices::replyFinisheddeleteListByID(QNetworkReply *reply)
{
    qDebug() << "Response of delete: "<< (QString)reply->readAll();
}
void ListServices::replyFinishedcreateList(QNetworkReply *reply)
{
   qDebug() << "Response of create: "<< (QString)reply->readAll();
}
void ListServices::replyFinishedupdateList(QNetworkReply *reply)
{
     qDebug() << "Response of update: "<< (QString)reply->readAll();
}
List* ListServices::getListByID(int _listID)
{

        this->list = new List();
        QUrl qrl(this->pref.baseUrl+this->baseUrlList + QString::number(_listID));
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetListByID(QNetworkReply*)));
        QNetworkRequest request(qrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept-Language", "en-US;q=1.0");
        manager->get(request);
        QEventLoop loop;
        connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
        loop.exec();
        return this->list;
}
vector<List*> ListServices::getLists()
{
    this->listLists.clear();
        QUrl qrl(this->pref.baseUrl + this->baseUrlList);
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetLists(QNetworkReply*)));
        QNetworkRequest request(qrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept-Language", "en-US;q=1.0");
        manager->get(request);
        QEventLoop loop;
        connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
        loop.exec();
        return this->listLists;
}
void ListServices::deleteListByID(int _listID)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlList + QString::number(_listID));
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinisheddeleteListByID(QNetworkReply*)));
        QNetworkRequest request(qrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept-Language", "en-US;q=1.0");
        manager->deleteResource(request);
}
void ListServices::createList(List* l)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlList);
    QJsonObject json_obj_list;
    QNetworkRequest request(qrl);
    json_obj_list = mapperListToJsonObject(l,false);
    manager = new QNetworkAccessManager(this);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept-Language", "en-US;q=1.0");
        QJsonDocument doc(json_obj_list);
        manager->post(request, doc.toJson(QJsonDocument::Compact));
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedcreateList(QNetworkReply*)));
}
void ListServices::updateList(List* l)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlList + QString::number(l->listID));
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedupdateList(QNetworkReply*)));
        QNetworkRequest request(qrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Accept-Language", "en-US;q=1.0");
        QJsonObject json_obj_list = mapperListToJsonObject(l,true);
        QJsonDocument doc(json_obj_list);
        QByteArray bytes = doc.toJson();
        manager->put(request,bytes);
}

inline List* ListServices::mapperList(QJsonObject list)
{
    List* l = new List();
    vector<int> arrayCreateDate = getDateFromDateDB(list["createdate"].toString());
    vector<int> arrayDeleteDate = getDateFromDateDB(list["deletedate"].toString());
    vector<Item*> _listItem;
    vector<Permission*> _listPermission;
    l->listID = list["listeid"].toInt();
    l->userID = list["userid"].toObject()["userid"].toInt();
    l->listItem = vector<Item*>{};
    l->listPermission = vector<Permission*>{};
    l->color = list["color"].toString();
    l->description = list["description"].toString();
    l->isDeleted = list["isdeleted"].toBool();
    l->createDate = QDate(arrayCreateDate.at(0),arrayCreateDate.at(1),arrayCreateDate.at(2));
    l->deleteDate = QDate(arrayDeleteDate.at(0),arrayDeleteDate.at(1),arrayDeleteDate.at(2));
    return l;
}
inline QJsonObject ListServices::mapperListToJsonObject(List* l,bool listIDIN)
{
    QJsonObject json_obj_list;
    QJsonObject json_obj_user;
    User* u = new User();
    u = this->userServ.getUserByID(l->userID);

    //USER OBJ TO JSON
    json_obj_user.insert("login",u->login);
    json_obj_user.insert("name",u->name);
    json_obj_user.insert("password",u->password);
    json_obj_user.insert("userid",u->userID);
    //USER OBJ TO JSON

    json_obj_list.insert("color", l->color);
    json_obj_list.insert("createdate", QDateTime(l->createDate).toString(Qt::ISODate));
    json_obj_list.insert("deleteddate", QDateTime(l->deleteDate).toString(Qt::ISODate));
    json_obj_list.insert("description", l->description);
    json_obj_list.insert("isdeleted", l->isDeleted);
    json_obj_list.insert("userid", json_obj_user);
    if(listIDIN)
    {
        json_obj_list.insert("listeid", l->listID);
    }
    return json_obj_list;
}
inline vector<int> ListServices::getDateFromDateDB(QString date)
{

    QString strCreateDate = date.section("T",0,0);
    int yearDate = strCreateDate.section("-",0,0).toInt();
    int monthDate = strCreateDate.section("-",1,1).toInt();
    int dayDate = strCreateDate.section("-",2,2).toInt();
    return vector<int> {yearDate,monthDate,dayDate};
}
