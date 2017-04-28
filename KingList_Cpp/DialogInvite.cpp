#include "dialog_invite.h"
#include "ui_dialog_invite.h"
#include <QMessageBox>
#include "util_repository.h"

Repository repository = Repository();

InviteDialog::InviteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InviteDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("Invite");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));
}

InviteDialog::~InviteDialog()
{
    delete ui;
}

Permission* InviteDialog::getPermission(){
    return this->newPermission;
}


void InviteDialog::on_btn_cancel_clicked()
{
    this->done(0);
}

void InviteDialog::on_btn_share_clicked()
{
    this->newPermission = new Permission();

    User* user = repository.getUserByLogin(ui->lineEdit->text());
    if(user){
        this->newPermission = new Permission(user->userID,0,ui->canCheck->isChecked(), ui->canWrite->isChecked(), ui->canDelete->isChecked(), ui->canShare->isChecked());
        this->done(1);
    }
    else{
        QMessageBox::critical(this,tr("Wrong Login"),tr("This User Cannot be Found!"));
    }
}
