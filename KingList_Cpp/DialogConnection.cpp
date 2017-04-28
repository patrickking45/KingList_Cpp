#include "dialog_connection.h"
#include "ui_dialog_connection.h"

#include "model_user.h"
#include "util_repository.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

Repository* repository = new Repository();

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    this->user = new User();

    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("Connection");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));
}

inline ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_btn_connect_clicked()
{
    this->user = new User();
    this->user->login = ui->txt_login->text();
    this->user->password = ui->txt_passwd->text();

    this->user = repository->connect(this->user);

    if(this->user){
        this->done(1);
    }
    else{
        QMessageBox::critical(this,tr("Wrong Password"),tr("Your Login or Password is Invalid!"));
    }
}

User* ConnectionDialog::getUser(){
    return this->user;
}
