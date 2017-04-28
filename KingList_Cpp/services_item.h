#ifndef ITEMSERVICES_H
#define ITEMSERVICES_H
#include <QObject>
#include <QtCore>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <vector>
#include "model_item.h"
#include <QMetaType>
#include "util_preferences.h"
#include "services_user.h"
#include "services_list.h"

class ItemServices : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;
    std::vector<Item*> listItems;
    Item* item;
    PREFERENCES pref;
    QString baseUrlItem = QString("model.item/");
    UserServices userServ;
    ListServices listServ;


signals:
    void mapFinished();


private slots:
  void replyFinishedgetItems(QNetworkReply *);
  void replyFinishedgetItemByID(QNetworkReply *);
  void replyFinisheddeleteItemByID(QNetworkReply *);
  void replyFinishedcreateItem(QNetworkReply *);
  void replyFinishedupdateItem(QNetworkReply *);
public:

  vector<Item*> getItems();
  Item* getItemByID(int);
  void deleteItemByID(int);
  void createItem(Item*);
  void updateItem(Item*);

  vector<int> getDateFromDateDB(QString);
  Item* mapperItem(QJsonObject);
  QJsonObject mapperItemToJsonObject(Item*,bool);
};


#endif // ITEMSERVICES_H
