#ifndef ITEM_H
#define ITEM_H
#include <QString>
#include <QDate>
#include <QMetaType>
#include <iostream>

using namespace std;

class Item
{
public:
    int itemID;
    int userID;
    string title;
    QPixmap image;
    QDate createDate;
    QDate checkDate;
    bool isChecked;
    QDate deleteDate;
    bool isDeleted;
    bool isPinned;
    bool isFavorite;

       Item(){}
       Item(int,int,string,QDate,QDate,bool,QDate,bool,bool,bool);
       Item(int,string,QDate,QDate,bool,QDate,bool,bool,bool);

    void setPin();
    void setFav();
    void setImg();
    void del();
};

Item::Item(int _itemID, int _userID, string _title, QDate _createDate, QDate _checkDate, bool _isChecked, QDate _deleteDate, bool _isDeleted, bool _isPinned, bool _isFavorite)
{
    this->itemID = _itemID;
    this->userID = _userID;
    this->title = _title;
    this->createDate = _createDate;
    this->checkDate = _checkDate;
    this->isChecked = _isChecked;
    this->deleteDate = _deleteDate;
    this->isDeleted= _isDeleted;
    this->isPinned = _isPinned;
    this->isFavorite = _isFavorite;
}

Item::Item( int _userID, string _title, QDate _createDate, QDate _checkDate, bool _isChecked, QDate _deleteDate, bool _isDeleted,bool _isPinned, bool _isFavorite)
{
    this->userID = _userID;
    this->title = _title;
    this->createDate = _createDate;
    this->checkDate = _checkDate;
    this->isChecked = _isChecked;
    this->deleteDate = _deleteDate;
    this->isDeleted= _isDeleted;
    this->isPinned = _isPinned;
    this->isFavorite = _isFavorite;
}

void Item::setPin(){
    this->isPinned = (this->isPinned)? false:true;
}

void Item::setFav(){
    this->isFavorite = (this->isFavorite)? false:true;
}

void Item::setImg(){
    cout << "Setting Img: " << this->title << endl;
}

void Item::del(){
    cout << "Deleting: " << this->title << endl;
}

Q_DECLARE_METATYPE(Item*)

#endif // ITEM_H
