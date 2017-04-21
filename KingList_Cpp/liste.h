#ifndef LISTE_H
#define LISTE_H
#include "item.h"
#include "permission.h"
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
    string color;
    string description;
    QDate createDate;
    QDate deleteDate;
    bool isDeleted;

    List(){}
    List(int,int,vector<Item*>,vector<Permission*>,string,string,QDate,QDate,bool);
    List(int,vector<Item*>,vector<Permission*>,string,string,QDate,QDate,bool);
    List(int,string,string);

    Item* getItem(int);
};

inline List::List(int _listID, int _userID,vector<Item*> _listItem,vector<Permission*> _listPermission,string _color,string _description,QDate _createDate,QDate _deleteDate, bool _isDeleted)
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

inline List::List(int _userID,vector<Item*> _listItem,vector<Permission*> _listPermission,string _color,string _description,QDate _createDate,QDate _deleteDate, bool _isDeleted)
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

inline List::List(int _userID,string _description,string _color)
{
    vector<Item*> items;
    vector<Permission*> permissions;

    this->userID= _userID;
    this->listItem = items;
    this->listPermission = permissions;
    this->color = _color;
    this->description = _description;
    this->createDate = QDate();
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

Q_DECLARE_METATYPE(List*)

#endif // LISTE_H
