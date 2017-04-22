#ifndef PERMISSION_H
#define PERMISSION_H
#include <QString>
#include <QMetaType>

class Permission
{
public:
    int userID;
    int permID;
    bool canWrite;
    bool canCheck;
    bool canDelete;
    bool canShare;

     Permission(){}
     Permission(int,int,bool,bool,bool,bool);
     Permission(int,bool,bool,bool,bool);
};
inline Permission::Permission(int _permID, int _userID, bool _canCheck, bool _canWrite, bool _canDelete, bool _canShare)
{
    this->permID = _permID;
    this->userID = _userID;
    this->canWrite = _canWrite;
    this->canCheck = _canCheck;
    this->canDelete = _canDelete;
    this->canShare = _canShare;
}

inline Permission::Permission(int _userID, bool _canCheck, bool _canWrite, bool _canDelete, bool _canShare)
{
    this->userID = _userID;
    this->canWrite = _canWrite;
    this->canCheck = _canCheck;
    this->canDelete = _canDelete;
    this->canShare = _canShare;
}

Q_DECLARE_METATYPE(Permission*)



#endif // PERMISSION_H
