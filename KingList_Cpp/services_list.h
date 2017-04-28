#ifndef LISTSERVICES_H
#define LISTSERVICES_H
#include <QObject>
#include <QtCore>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <vector>
#include <QString>
#include "model_liste.h"
#include <QMetaType>
#include <QObject>
#include "util_preferences.h"
#include "services_user.h"

class ListServices : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;
public:
    std::vector<List*> listLists;
    List* list;
    PREFERENCES pref;
    QString baseUrlList = QString("model.liste/");
    UserServices userServ;

signals:
    void mapFinished();

private slots:
    void replyFinishedgetLists(QNetworkReply *);
    void replyFinishedgetListByID(QNetworkReply *);
    void replyFinisheddeleteListByID(QNetworkReply *);
    void replyFinishedcreateList(QNetworkReply *);
    void replyFinishedupdateList(QNetworkReply *);
public:
    vector<List*> getLists();
    List* getListByID(int);
    void deleteListByID(int);
    void createList(List*);
    void updateList(List*);

    QJsonObject mapperListToJsonObject(List*,bool);
    List* mapperList(QJsonObject);
    vector<int> getDateFromDateDB(QString);

};

#endif // LISTSERVICES_H
