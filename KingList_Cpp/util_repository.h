#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "model_liste.h"
#include "model_item.h"
#include "model_user.h"
#include "model_permission.h"

#include "services_item.h"
#include "services_list.h"
#include "services_permission.h"
#include "services_user.h"

using namespace std;

class Repository{
public:
    vector<List*> listOfLists;

    ItemServices* itemService = new ItemServices();
    ListServices* listService = new ListServices();
    UserServices* userService = new UserServices();
    PermissionServices* permService = new PermissionServices();

    Repository(){
        //this->Init();
    }
    ~Repository(){}
    inline void Init(){
        this->listOfLists.clear();

        vector<Item*> items;
        vector<Permission*> permissions;

        items.push_back(new Item(11, 154887, "Spaghetti", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, true));
        items.push_back(new Item(12, 154887, "Burrito", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, false, true));
        items.push_back(new Item(13, 154887, "Pizza", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, false));

        permissions.push_back(new Permission(332, 101, true, true, true, true));
        permissions.push_back(new Permission(333, 102, true, false, true, false));
        permissions.push_back(new Permission(334, 103, true, true, false, true));
        permissions.push_back(new Permission(335, 104, true, false, true, true));
        permissions.push_back(new Permission(336, 115, true, false, false, false));

        this->listOfLists.push_back(new List(1,100,items,permissions,"96,69,42","Épicerie",QDate(2017,04,18),QDate(1,1,1), false));

        items.clear();
        items.push_back(new Item(21, 154887, "John Wick 2", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, false, true));
        items.push_back(new Item(22, 154887, "Guardians of The Galaxy 2", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, true, false));
        items.push_back(new Item(23, 154887, "Thor: Ragnarok", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, true));
        items.push_back(new Item(24, 154887, "Histoire de Jouet 3", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, false, false));

        permissions.clear();
        permissions.push_back(new Permission(334, 103, true, true, false, true));
        permissions.push_back(new Permission(335, 104, true, false, true, true));
        permissions.push_back(new Permission(336, 115, true, false, false, false));

        this->listOfLists.push_back(new List(2,2,items,permissions,"255,250,240","Films",QDate(2017,04,18),QDate(1,1,1), false));

        items.clear();
        items.push_back(new Item(31, 154887, "Android", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, false, false));
        items.push_back(new Item(32, 154887, "Linux", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, false));
        items.push_back(new Item(33, 154887, "C++", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, true, false));
        items.push_back(new Item(34, 154887, "Angular", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, false, true));
        items.push_back(new Item(35, 154887, "Java EE", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, false));

        permissions.clear();

        this->listOfLists.push_back(new List(3,3,items,permissions,"200,169,113","Devoir",QDate(2017,04,18),QDate(1,1,1), false));

        items.clear();

        permissions.clear();

        items.push_back(new Item(35, 154887, "Confirmation Upload", QDate(2017,04,18), QDate(2017,04,18), false, QDate(1,1,1), false, false, false));
        items.push_back(new Item(35, 154887, "Confirmation Delete Share", QDate(2017,04,18), QDate(2017,04,18), false, QDate(1,1,1), false, false, false));
        items.push_back(new Item(35, 154887, "Button Add Item Sans Liste Selectionné", QDate(2017,04,18), QDate(2017,04,18), false, QDate(1,1,1), false, false, false));
        this->listOfLists.push_back(new List(4,4,items,permissions,"100,150,225","To Do",QDate(2017,04,18),QDate(1,1,1), false));
    }
    inline vector<List*> getListOfUser(int userId){
        vector<List*> userLists;

        vector<List*> allLists = listService->getLists();
        vector<Item*> allItems = itemService->getItems();
        vector<Permission*> allPermissions = permService->getPermissions();

        for(List* list : allLists){
            for(Permission* perm : allPermissions){
                if(perm->listID == list->listID){
                    list->addPermission(perm);
                }
            }
            for(Item* item : allItems){
                if(item->listID == list->listID){
                    list->addItem(item);
                }
            }

            if(list->userID == userId){
                userLists.push_back(list);
            }
            else{
                for(Permission* perm : list->listPermission){
                    if(perm->userID == userId){
                        userLists.push_back(list);
                    }
                }
            }
        }

        return userLists;
    }

    inline void deleteItem(Item* item){
        itemService->deleteItemByID(item->itemID);
    }

    inline void saveItem(Item* item){
        itemService->updateItem(item);
    }

    inline void createItem(Item* item){
        itemService->createItem(item);
    }

    inline void deleteList(List* list){
        listService->deleteListByID(list->listID);
    }

    inline void saveList(List* list){
        listService->updateList(list);
    }

    inline void createList(List* list){
        listService->createList(list);
    }

    inline void deletePermission(Permission* permission){
        permService->deletePermission(permission);
    }

    inline void savePermission(Permission* permission){
        permService->updatePermission(permission);
    }

    inline void createPermission(Permission* permission){
        permService->createPermission(permission);
    }

    inline User* connect(User* connectingUser){
        User* connectedUser = NULL;

        for(User* user : userService->getUsers()){
            if(user->getLogin() == connectingUser->getLogin() && user->getPassword() == connectingUser->getPassword()){
                connectedUser = user;
            }
        }

        return connectedUser;
    }

    inline User* getUserById(int userID){
        return userService->getUserByID(userID);
    }

    inline User* getUserByLogin(QString login){
        User* foundUser = NULL;

        for(User* user : userService->getUsers()){
            if(user->getLogin() == login){
                foundUser = user;
            }
        }

        return foundUser;

    }

    inline void saveUser(User* user){
        userService->updateUser(user);
    }

    inline void createUser(User* user){
        userService->createUser(user);
    }

};

#endif // REPOSITORY_H
