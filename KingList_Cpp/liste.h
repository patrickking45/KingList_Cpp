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
    vector<Item*> listItem;
    vector<Permission*> listPermission;
    string color;
    string description;
    QDate createDate;
    QDate deleteDate;
    bool isDeleted;

    List(){}
    List(int,vector<Item*>,vector<Permission*>,string,string,QDate,QDate,bool);
    List(vector<Item*>,vector<Permission*>,string,string,QDate,QDate,bool);

    Item* getItem(int);
};

List::List(int _listID,vector<Item*> _listItem,vector<Permission*> _listPermission,string _color,string _description,QDate _createDate,QDate _deleteDate, bool _isDeleted)
{
    this->listID = _listID;
    this->listItem = _listItem;
    this->listPermission = _listPermission;
    this->color = _color;
    this->description = _description;
    this->createDate = _createDate;
    this->deleteDate = _deleteDate;
    this->isDeleted = _isDeleted;
}

List::List(vector<Item*> _listItem,vector<Permission*> _listPermission,string _color,string _description,QDate _createDate,QDate _deleteDate, bool _isDeleted)
{
    this->listItem = _listItem;
    this->listPermission = _listPermission;
    this->color = _color;
    this->description = _description;
    this->createDate = _createDate;
    this->deleteDate = _deleteDate;
    this->isDeleted = _isDeleted;
}

Item* List::getItem(int id){
    for(Item* &item : this->listItem){
        if(item->itemID == id){
            return item;
        }
    }
    return NULL;
}

Q_DECLARE_METATYPE(List*)

#endif // LISTE_H
