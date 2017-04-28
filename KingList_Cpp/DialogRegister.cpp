#include "dialog_register.h"
#include "ui_dialog_register.h"
#include "model_user.h"
#include "util_repository.h"

DialogRegister::DialogRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRegister)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("Registration");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));
}

Repository* repositoryReg = new Repository();

DialogRegister::~DialogRegister()
{
    delete ui;
}

void DialogRegister::on_btn_register_clicked()
{
    User* user = new User();
    user->name = ui->txt_name->text();
    user->login = ui->txt_login->text();
    user->password = ui->txt_passwd->text();

    repositoryReg->createUser(user);

    this->done(1);

}
