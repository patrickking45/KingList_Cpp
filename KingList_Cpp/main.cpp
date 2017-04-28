#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <QObject>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap splashPixmap = QPixmap(":/new/Logo/Icons/Logo/KingList-Splash.png").scaled(QSize(1000,1000),  Qt::KeepAspectRatio);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(splashPixmap);
    splash->show();

    MainWindow w;

    QTimer::singleShot(1000,splash,SLOT(close()));
    QTimer::singleShot(1000,&w,SLOT(show()));

    return a.exec();
}
