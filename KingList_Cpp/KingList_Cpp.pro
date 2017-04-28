#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T16:39:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KingList_Cpp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    utility.cpp \
    DialogConnection.cpp \
    DialogAddItem.cpp \
    DialogDisplayImage.cpp \
    DialogInvite.cpp \
    DialogNewList.cpp \
    DialogSharing.cpp \
    ServicesItem.cpp \
    ServicesList.cpp \
    ServicesPermission.cpp \
    ServicesUser.cpp \
    DialogRegister.cpp

HEADERS  += mainwindow.h \
    dialog_connection.h \
    dialog_additem.h \
    dialog_displayimage.h \
    dialog_invite.h \
    dialog_newlist.h \
    dialog_sharing.h \
    services_item.h \
    services_list.h \
    services_permission.h \
    services_user.h \
    model_user.h \
    model_permission.h \
    model_item.h \
    model_liste.h \
    util_repository.h \
    util_preferences.h \
    dialog_register.h

FORMS    += mainwindow.ui \
    dialog_connection.ui \
    dialog_additem.ui \
    dialog_displayimage.ui \
    dialog_invite.ui \
    dialog_newlist.ui \
    dialog_sharing.ui \
    dialog_register.ui

RESOURCES += \
    resources.qrc
