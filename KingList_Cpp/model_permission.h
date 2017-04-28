#ifndef PERMISSION_H
#define PERMISSION_H
#include <QString>
#include <QMetaType>

class Permission
{
public:
    int userID;
    int listID;
    int permID;
    bool canWrite;
    bool canCheck;
    bool canDelete;
    bool canShare;

     Permission(){}
     Permission(int,int,int,bool,bool,bool,bool);
     Permission(int,int,bool,bool,bool,bool);

     void setCheck();
     void setWrite();
     void setDelete();
     void setShare();
};
inline Permission::Permission(int _permID, int _userID,int _listID, bool _canCheck, bool _canWrite, bool _canDelete, bool _canShare)
{
    this->permID = _permID;
    this->userID = _userID;
    this->canWrite = _canWrite;
    this->canCheck = _canCheck;
    this->canDelete = _canDelete;
    this->canShare = _canShare;
}

inline Permission::Permission(int _userID, int _listID, bool _canCheck, bool _canWrite, bool _canDelete, bool _canShare)
{
    this->userID = _userID;
    this->listID = _listID;
    this->canWrite = _canWrite;
    this->canCheck = _canCheck;
    this->canDelete = _canDelete;
    this->canShare = _canShare;
}

inline void Permission::setCheck(){
    this->canCheck = (this->canCheck)? false:true;
}

inline void Permission::setWrite(){
    this->canWrite = (this->canWrite)? false:true;
}

inline void Permission::setDelete(){
    this->canDelete = (this->canDelete)? false:true;
}

inline void Permission::setShare(){
    this->canShare = (this->canShare)? false:true;
}

Q_DECLARE_METATYPE(Permission*)



#endif // PERMISSION_H
