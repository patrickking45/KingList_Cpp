#ifndef LISTE_H
#define LISTE_H
#include "model_item.h"
#include "model_permission.h"
#include <QMetaType>
#include <QString>
#include <QDate>
#include <iostream>

class List
{
public:
    int listID;
    int userID;
    vector<Item*> listItem;
    vector<Permission*> listPermission;
    QString color;
    QString description;
    QDate createDate;
    QDate deleteDate;
    bool isDeleted;

    List(){}
    List(int,int,vector<Item*>,vector<Permission*>,QString,QString,QDate,QDate,bool);
    List(int,vector<Item*>,vector<Permission*>,QString,QString,QDate,QDate,bool);
    List(int,QString,QString);

    Item* getItem(int);

    void addItem(Item*);
    void addPermission(Permission*);

    bool UserIsOwner(int);
    bool UserCanCheck(int);
    bool UserCanPin(int);
    bool UserCanWrite(int);
    bool UserCanDelete(int);
    bool UserCanShare(int);
};

inline List::List(int _listID, int _userID,vector<Item*> _listItem,vector<Permission*> _listPermission,QString _color,QString _description,QDate _createDate,QDate _deleteDate, bool _isDeleted)
{
    this->listID = _listID;
    this->userID = _userID;
    this->listItem = _listItem;
    this->listPermission = _listPermission;
    this->color = _color;
    this->description = _description;
    this->createDate = _createDate;
    this->deleteDate = _deleteDate;
    this->isDeleted = _isDeleted;
}

inline List::List(int _userID,vector<Item*> _listItem,vector<Permission*> _listPermission,QString _color,QString _description,QDate _createDate,QDate _deleteDate, bool _isDeleted)
{
    this->userID = _userID;
    this->listItem = _listItem;
    this->listPermission = _listPermission;
    this->color = _color;
    this->description = _description;
    this->createDate = _createDate;
    this->deleteDate = _deleteDate;
    this->isDeleted = _isDeleted;
}

inline List::List(int _userID,QString _description,QString _color)
{
    vector<Item*> items;
    vector<Permission*> permissions;

    this->userID= _userID;
    this->listItem = items;
    this->listPermission = permissions;
    this->color = _color;
    this->description = _description;
    this->createDate = QDate::currentDate();
    this->deleteDate = QDate(1,1,1);
    this->isDeleted = false;
}

inline Item* List::getItem(int id){
    for(Item* &item : this->listItem){
        if(item->itemID == id){
            return item;
        }
    }
    return NULL;
}

inline void List::addItem(Item* item){
    this->listItem.push_back(item);
}

inline void List::addPermission(Permission* permission){
    this->listPermission.push_back(permission);
}

inline bool List::UserIsOwner(int userId){
    if(userId == this->userID){
        return true;
    }

    return false;
}

inline bool List::UserCanCheck(int userId){
    if(userId == this->userID){
        return true;
    }

    for(Permission* permission : this->listPermission){
        if(permission->userID == userId){
            return permission->canCheck;
        }
    }

    return false;
}

inline bool List::UserCanWrite(int userId){
    if(userId == this->userID){
        return true;
    }

    for(Permission* permission : this->listPermission){
        if(permission->userID == userId){
            return permission->canWrite;
        }
    }

    return false;
}

inline bool List::UserCanDelete(int userId){
    if(userId == this->userID){
        return true;
    }

    for(Permission* permission : this->listPermission){
        if(permission->userID == userId){
            return permission->canDelete;
        }
    }

    return false;
}

inline bool List::UserCanPin(int userId){
    if(userId == this->userID){
        return true;
    }

    return false;
}

inline bool List::UserCanShare(int userId){
    if(userId == this->userID){
        return true;
    }

    for(Permission* permission : this->listPermission){
        if(permission->userID == userId){
            return permission->canShare;
        }
    }

    return false;
}

Q_DECLARE_METATYPE(List*)

#endif // LISTE_H
