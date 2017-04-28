#include "dialog_sharing.h"
#include "ui_dialog_sharing.h"

#include <QSignalMapper>
#include <QPushButton>
#include <iostream>
#include <QMessageBox>
#include <QLayout>

#include "dialog_invite.h"
#include "util_repository.h"

using namespace std;

vector<Permission*> listPermissions;
Repository* repo = new Repository();
int listID;

SharingDialog::SharingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SharingDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("Sharing");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));

    this->showShares();
}

void SharingDialog::showShares(){
    QTableWidgetItem *tableItem = 0;
    int Icon_Size = 50;

    ui->sharingTable->clear();
    ui->sharingTable->horizontalHeader()->hide();
    ui->sharingTable->verticalHeader()->hide();
    ui->sharingTable->setShowGrid(false);
    ui->sharingTable->viewport()->setFocusPolicy(Qt::NoFocus);
    ui->sharingTable->setColumnCount(6);

    ui->sharingTable->setColumnWidth(0,150);
    ui->sharingTable->setColumnWidth(1,40);
    ui->sharingTable->setColumnWidth(2,40);
    ui->sharingTable->setColumnWidth(3,40);
    ui->sharingTable->setColumnWidth(4,40);
    ui->sharingTable->setColumnWidth(5,40);

    ui->sharingTable->setRowCount(listPermissions.size());

    for(int i=0; i<listPermissions.size();i++){
        Permission* perm = listPermissions[i];
        Qt::CheckState canCheck = ((perm->canCheck) ? Qt::Checked : Qt::Unchecked);
        Qt::CheckState canWrite = ((perm->canWrite) ? Qt::Checked : Qt::Unchecked);
        Qt::CheckState canDelete = ((perm->canDelete) ? Qt::Checked : Qt::Unchecked);
        Qt::CheckState canShare = ((perm->canShare) ? Qt::Checked : Qt::Unchecked);

        QSignalMapper* signalMapperCanCheck;
        QSignalMapper* signalMapperCanWrite;
        QSignalMapper* signalMapperCanDelete;
        QSignalMapper* signalMapperCanShare;
        QSignalMapper* signalMapperUnShare;

        signalMapperCanCheck = new QSignalMapper(this);
        connect(signalMapperCanCheck, SIGNAL(mapped(int)), this, SLOT(clickedCheck(int)));

        signalMapperCanWrite = new QSignalMapper(this);
        connect(signalMapperCanWrite, SIGNAL(mapped(int)), this, SLOT(clickedWrite(int)));

        signalMapperCanDelete = new QSignalMapper(this);
        connect(signalMapperCanDelete, SIGNAL(mapped(int)), this, SLOT(clickedDelete(int)));

        signalMapperCanShare = new QSignalMapper(this);
        connect(signalMapperCanShare, SIGNAL(mapped(int)), this, SLOT(clickedShare(int)));

        signalMapperUnShare = new QSignalMapper(this);
        connect(signalMapperUnShare, SIGNAL(mapped(int)), this, SLOT(clickedUnShare(int)));

        QVariant qv;
        qv.setValue(perm);

        /* Item Name */
        User* user = repo->getUserById(perm->userID);
        if(user){
            tableItem = new QTableWidgetItem(user->getLogin());
        }
        else{
            tableItem = new QTableWidgetItem("UNKNOWN");
        }

        /* Can Check Button */
        QPushButton* btn_can_check = new QPushButton();
        signalMapperCanCheck->setMapping(btn_can_check, perm->permID);
        connect(btn_can_check, SIGNAL(clicked()), signalMapperCanCheck, SLOT(map()));
        btn_can_check->setCheckable(true);
        btn_can_check->setChecked(canCheck);

        QIcon ico_check;
        ico_check.addFile(":/new/IconsSharing/Icons/Sharing/check_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_check.addFile(":/new/IconsSharing/Icons/Sharing/check_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_can_check->setIcon(ico_check);
        btn_can_check->setFlat(true);
        btn_can_check->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Can Write Button */
        QPushButton* btn_can_write = new QPushButton();
        signalMapperCanWrite->setMapping(btn_can_write, perm->permID);
        connect(btn_can_write, SIGNAL(clicked()), signalMapperCanWrite, SLOT(map()));
        btn_can_write->setCheckable(true);
        btn_can_write->setChecked(canWrite);

        QIcon ico_write;
        ico_write.addFile(":/new/IconsSharing/Icons/Sharing/write_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_write.addFile(":/new/IconsSharing/Icons/Sharing/write_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_can_write->setIcon(ico_write);
        btn_can_write->setFlat(true);
        btn_can_write->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Can Delete Button */
        QPushButton* btn_can_delete = new QPushButton();
        signalMapperCanDelete->setMapping(btn_can_delete, perm->permID);
        connect(btn_can_delete, SIGNAL(clicked()), signalMapperCanDelete, SLOT(map()));
        btn_can_delete->setCheckable(true);
        btn_can_delete->setChecked(canDelete);

        QIcon ico_delete;
        ico_delete.addFile(":/new/IconsSharing/Icons/Sharing/delete_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_delete.addFile(":/new/IconsSharing/Icons/Sharing/delete_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_can_delete->setIcon(ico_delete);
        btn_can_delete->setFlat(true);
        btn_can_delete->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Can Share Button */
        QPushButton* btn_can_share = new QPushButton();
        signalMapperCanShare->setMapping(btn_can_share, perm->permID);
        connect(btn_can_share, SIGNAL(clicked()), signalMapperCanShare, SLOT(map()));
        btn_can_share->setCheckable(true);
        btn_can_share->setChecked(canShare);

        QIcon ico_share;
        ico_share.addFile(":/new/IconsSharing/Icons/Sharing/share_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_share.addFile(":/new/IconsSharing/Icons/Sharing/share_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_can_share->setIcon(ico_share);
        btn_can_share->setFlat(true);
        btn_can_share->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");

        /* Unshare Button */
        QPushButton* btn_unshare = new QPushButton();
        signalMapperUnShare->setMapping(btn_unshare, perm->permID);
        connect(btn_unshare, SIGNAL(clicked()), signalMapperUnShare, SLOT(map()));

        QIcon ico_unshare;
        ico_unshare.addFile(":/new/IconsSharing/Icons/Sharing/remove_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_unshare.addFile(":/new/IconsSharing/Icons/Sharing/remove_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_unshare->setIcon(ico_unshare);
        btn_unshare->setFlat(true);
        btn_unshare->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Setting Widget In Table*/
        ui->sharingTable->setItem(i,0,tableItem);
        ui->sharingTable->setCellWidget(i,1,btn_can_check);
        ui->sharingTable->setCellWidget(i,2,btn_can_write);
        ui->sharingTable->setCellWidget(i,3,btn_can_delete);
        ui->sharingTable->setCellWidget(i,4,btn_can_share);
        ui->sharingTable->setCellWidget(i,5,btn_unshare);
    }

    ui->sharingTable->show();
}

vector<Permission*> SharingDialog::getPermissions(){
    return listPermissions;
}

Permission* SharingDialog::getPermissionById(int id){
    for(int i = 0; i<listPermissions.size(); i++){
        if(listPermissions[i]->permID == id){
            return listPermissions[i];
        }
    }
    return NULL;
}

SharingDialog::~SharingDialog()
{
    delete ui;
}

void SharingDialog::setPermissions(vector<Permission*> perms, int _listID){
    listPermissions = perms;
    listID = _listID;
    this->showShares();
}

void SharingDialog::clickedCheck(int buttonId){
    this->getPermissionById(buttonId)->setCheck();
    repo->savePermission(this->getPermissionById(buttonId));
}

void SharingDialog::clickedWrite(int buttonId){
    this->getPermissionById(buttonId)->setWrite();
    repo->savePermission(this->getPermissionById(buttonId));
}

void SharingDialog::clickedDelete(int buttonId){
    this->getPermissionById(buttonId)->setDelete();
    repo->savePermission(this->getPermissionById(buttonId));
}

void SharingDialog::clickedShare(int buttonId){
    this->getPermissionById(buttonId)->setShare();
    repo->savePermission(this->getPermissionById(buttonId));
}

void SharingDialog::clickedUnShare(int buttonId){
    QMessageBox confirmationBox;
    confirmationBox.setText(QString("Are you sure you want to stop sharing with this user?"));
    confirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if(confirmationBox.exec() == QMessageBox::Yes){
        repo->deletePermission(this->getPermissionById(buttonId));
        listPermissions.erase(remove(listPermissions.begin(), listPermissions.end(), this->getPermissionById(buttonId)),listPermissions.end());
        this->showShares();
    }
}

void SharingDialog::on_pushButton_clicked()
{
    InviteDialog inviteDialog;
    inviteDialog.setModal(true);
    if(inviteDialog.exec()){
        Permission* newPerm = inviteDialog.getPermission();
        newPerm->listID=listID;
        listPermissions.push_back(newPerm);
        repo->createPermission(newPerm);
    }

    this->showShares();
}
