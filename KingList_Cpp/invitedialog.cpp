#include "invitedialog.h"
#include "ui_invitedialog.h"

InviteDialog::InviteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InviteDialog)
{
    ui->setupUi(this);
}

InviteDialog::~InviteDialog()
{
    delete ui;
}

Permission* InviteDialog::getPermission(){
    return new Permission(atoi(ui->lineEdit->text().toLatin1()),ui->canCheck->isChecked(), ui->canWrite->isChecked(), ui->canDelete->isChecked(), ui->canShare->isChecked());
}


void InviteDialog::on_btn_cancel_clicked()
{
    this->done(0);
}

void InviteDialog::on_btn_share_clicked()
{
    this->done(1);
}
