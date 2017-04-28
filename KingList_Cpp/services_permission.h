#ifndef PERMISSIONSERVICES_H
#define PERMISSIONSERVICES_H
#include <QObject>
#include <QtCore>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <vector>
#include "model_user.h"
#include "services_user.h"
#include "model_permission.h"
#include "util_preferences.h"
#include <QMetaType>
#include <QJsonObject>

class PermissionServices : public QObject
{
 Q_OBJECT
 QNetworkAccessManager *manager;

public:
    UserServices userServ;
    std::vector<Permission*> listPermissions;
    Permission* permission;
    PREFERENCES pref;
    QString baseUrlPermission = QString("model.permission/");
    Permission* mapperPermission(QJsonObject);
    QJsonObject mapperPermissionToJsonObject(Permission*);
signals:
    void mapFinished();

private slots:
  void replyFinishedgetPermissions(QNetworkReply *);
  void replyFinishedcreatePermission(QNetworkReply *);
  void replyFinishedupdatePermission(QNetworkReply *);
  void replyFinishedeletePermission (QNetworkReply *);

public:
  std::vector<Permission*> getPermissions();
  void createPermission(Permission*);
  void updatePermission(Permission*);
  void deletePermission(Permission*);
};

#endif // PERMISSIONSERVICES_H
