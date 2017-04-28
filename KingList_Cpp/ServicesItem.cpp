#include "services_item.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <iostream>
#include <QVariantMap>
#include <string>
#include "model_user.h"
#include <QString>
#include <QDate>
#include <QMetaType>
#include <iostream>
#include <QPixmap>
#include <QDateTime>
#include <QEventLoop>
using namespace std;


void ItemServices::replyFinishedgetItems(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonArray json_array = jsonResponse.array();
    foreach (const QJsonValue &value, json_array) {
            QJsonObject itemJson = value.toObject();
           Item* item = new Item();
           item = mapperItem(itemJson);
            this->listItems.push_back(item);
        }
    emit mapFinished();
}

void ItemServices::replyFinishedgetItemByID(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject itemJson = jsonResponse.object();
    this->item = mapperItem(itemJson);
    emit mapFinished();
}
void ItemServices::replyFinisheddeleteItemByID(QNetworkReply *reply)
{
    qDebug() << "Response of delete: "<< (QString)reply->readAll();
}
void ItemServices::replyFinishedcreateItem(QNetworkReply *reply)
{
    qDebug() << "Response of create: "<< (QString)reply->readAll();
}
void ItemServices::replyFinishedupdateItem(QNetworkReply *reply)
{
    qDebug() << "Response of update: "<< (QString)reply->readAll();
}

vector<Item*> ItemServices::getItems()
{
    this->listItems.clear();
    QUrl qrl(this->pref.baseUrl+this->baseUrlItem);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetItems(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->get(request);
    QEventLoop loop;
    connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
    loop.exec();
    return this->listItems;
}

Item* ItemServices::getItemByID(int _itemID)
{
    this->item = new Item();
    QUrl qrl(this->pref.baseUrl+this->baseUrlItem + QString::number(_itemID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedgetItemByID(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->get(request);
    QEventLoop loop;
    connect(this,SIGNAL(mapFinished()),&loop,SLOT(quit()));
    loop.exec();
    return this->item;

}
void ItemServices::deleteItemByID(int _itemID)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlItem + QString::number(_itemID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinisheddeleteItemByID(QNetworkReply*)));
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    manager->deleteResource(request);
}
void ItemServices::createItem(Item* _item)
{

    QUrl qrl(this->pref.baseUrl+this->baseUrlItem);
    QJsonObject json_obj_item = mapperItemToJsonObject(_item,false);
    manager = new QNetworkAccessManager(this);
    QNetworkRequest request(qrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    QJsonDocument doc(json_obj_item);
    manager->post(request, doc.toJson(QJsonDocument::Compact));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedcreateItem(QNetworkReply*)));
}
void ItemServices::updateItem(Item* _item)
{
    QUrl qrl(this->pref.baseUrl+this->baseUrlItem+ QString::number(_item->itemID));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedupdateItem(QNetworkReply*)));
    QNetworkRequest request(qrl);
    QJsonObject json_obj_item = mapperItemToJsonObject(_item,true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept-Language", "en-US;q=1.0");
    QJsonDocument doc(json_obj_item);
    QByteArray bytes = doc.toJson();
    manager->put(request,bytes);
}

inline Item* ItemServices::mapperItem(QJsonObject itemJson)
{
    Item* item = new Item();
    vector<int> arrayCreateDate = getDateFromDateDB(itemJson["createdate"].toString());
    vector<int> arrayDeleteDate = getDateFromDateDB(itemJson["deletedate"].toString());
    vector<int> arrayCheckDate = getDateFromDateDB(itemJson["checkdate"].toString());
    item->listID = itemJson["listid"].toObject()["listeid"].toInt();
    item->itemID = itemJson["itemid"].toInt();
    item->userID = itemJson["userid"].toObject()["userid"].toInt();
    item->title = itemJson["title"].toString();
    // on valider que le chemin de l'image n'est pas vide
    if (!itemJson["picture"].toString().isEmpty())
    {
      //item->image = QPixmap(itemJson["picture"].toString());
    }
    item->createDate = QDate(arrayCreateDate.at(0),arrayCreateDate.at(1),arrayCreateDate.at(2));
    item->checkDate = QDate(arrayCheckDate.at(0),arrayCheckDate.at(1),arrayCheckDate.at(2));
    item->deleteDate = QDate(arrayDeleteDate.at(0),arrayDeleteDate.at(1),arrayDeleteDate.at(2));
    item->isChecked = itemJson["ischecked"].toBool();
    item->isDeleted = itemJson["isdeleted"].toBool();
    item->isPinned = itemJson["ispinned"].toBool();
    item->isFavorite = itemJson["isfavorite"].toBool();
    return item;
}
inline QJsonObject ItemServices::mapperItemToJsonObject(Item* _item,bool itemIDIN)
{
    QJsonObject json_obj_item;

    QJsonObject json_obj_list;
    QJsonObject json_obj_user;

    //USER OBJ TO JSON
    List* l = listServ.getListByID(_item->listID);
    User* uList = this->userServ.getUserByID(l->userID);
    json_obj_user.insert("login",uList->login);
    json_obj_user.insert("name",uList->name);
    json_obj_user.insert("password",uList->password);
    json_obj_user.insert("userid",uList->userID);
    //USER OBJ TO JSON

    json_obj_list.insert("listeid", l->listID);
    json_obj_list.insert("color", l->color);
    json_obj_list.insert("createdate", QDateTime(l->createDate).toString(Qt::ISODate));
    json_obj_list.insert("deleteddate", QDateTime(l->deleteDate).toString(Qt::ISODate));
    json_obj_list.insert("description", l->description);
    json_obj_list.insert("isdeleted", l->isDeleted);
    json_obj_list.insert("userid", json_obj_user);
    //USER OBJ TO JSON


    User* u = this->userServ.getUserByID(_item->userID);
    QJsonObject json_obj_userItem = userServ.mapperUserToJsonObject(u,true);
    //USER OBJ TO JSON

    if(itemIDIN)
    {
      json_obj_item.insert("itemid", _item->itemID);
    }
    json_obj_item.insert("picture", "");
    json_obj_item.insert("userid", json_obj_userItem);
    json_obj_item.insert("title", _item->title);
    json_obj_item.insert("listid",json_obj_list);
    json_obj_item.insert("createdate", QDateTime(_item->createDate).toString(Qt::ISODate));
    json_obj_item.insert("checkdate", QDateTime(_item->checkDate).toString(Qt::ISODate));
    json_obj_item.insert("ischecked",_item->isChecked );
    json_obj_item.insert("deletedate", QDateTime(_item->deleteDate).toString(Qt::ISODate));
    json_obj_item.insert("isdeleted", _item->isDeleted );
    json_obj_item.insert("ispinned",_item->isPinned );
    json_obj_item.insert("isfavorite", _item->isFavorite );
    if(itemIDIN)
    {
        json_obj_item.insert("itemid", _item->itemID );
    }
   return json_obj_item;
}
inline vector<int> ItemServices::getDateFromDateDB(QString date)
{

    QString strCreateDate = date.section("T",0,0);
    int yearDate = strCreateDate.section("-",0,0).toInt();
    int monthDate = strCreateDate.section("-",1,1).toInt();
    int dayDate = strCreateDate.section("-",2,2).toInt();
    return vector<int> {yearDate,monthDate,dayDate};
}
