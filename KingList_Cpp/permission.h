#ifndef PERMISSION_H
#define PERMISSION_H
#include <QString>

class Permission
{
private:
     int userID;
     bool canWrite;
     bool canCheck;
     bool canDelete;
     bool canShare;

public:
     Permission(){}
     Permission(int,bool,bool,bool,bool);
     Permission(bool,bool,bool,bool);
};
inline Permission::Permission(int _userID, bool _canWrite, bool _canCheck, bool _canDelete, bool _canShare)
{
    this->userID = _userID;
    this->canWrite = _canWrite;
    this->canCheck = _canCheck;
    this->canDelete = _canDelete;
    this->canShare = _canShare;
}

inline Permission::Permission( bool _canWrite, bool _canCheck, bool _canDelete, bool _canShare)
{
    this->canWrite = _canWrite;
    this->canCheck = _canCheck;
    this->canDelete = _canDelete;
    this->canShare = _canShare;
}




#endif // PERMISSION_H
