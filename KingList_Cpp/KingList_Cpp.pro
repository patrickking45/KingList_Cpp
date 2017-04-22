#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T16:39:16
#
#-------------------------------------------------

QT       += core gui

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
    newlistdialog.cpp \
        mainwindow.cpp \
    sharingdialog.cpp \
    invitedialog.cpp \
    additemdialog.cpp \
    displayimagedialog.cpp

HEADERS  += mainwindow.h \
    permission.h \
    user.h \
    liste.h \
    item.h \
    newlistdialog.h \
    sharingdialog.h \
    invitedialog.h \
    additemdialog.h \
    displayimagedialog.h

FORMS    += mainwindow.ui \
    newlistdialog.ui \
    sharingdialog.ui \
    invitedialog.ui \
    additemdialog.ui \
    displayimagedialog.ui

RESOURCES += \
    resources.qrc
