#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model_liste.h"
#include "model_user.h"
#include "utility.cpp"
#include "util_repository.h"

#include <QSignalMapper>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <dialog_newlist.h>
#include <dialog_sharing.h>
#include <dialog_additem.h>
#include <dialog_connection.h>
#include <dialog_displayimage.h>
#include <dialog_register.h>

using namespace std;

List* actualList;
Repository repo = Repository();
static vector<List*> listOfLists;
QAction* sharing;
QAction* connexion;
QAction* deco;
QAction* reg;
User* connectedUser;

struct isImportant{
    inline bool operator() (const Item* item1, const Item* item2){
        return (item1->isFavorite > item2->isFavorite);
    }
};

List* getListById(int id){
    for(int i = 0 ; i < listOfLists.size(); i++){
        if(listOfLists[i]->listID == id){
            cout << "hey" << listOfLists[i]->description.toStdString() << endl;
            return listOfLists[i];
        }
    }
    return NULL;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
    //ToRemove
    repo.Init();

    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("KingList");
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));

    //Adding Actions
    sharing = new QAction(tr("&Partage"), this);
    sharing->setVisible(false);
    ui->menuBar->addAction(sharing);

    deco = new QAction(tr("&Déconnexion"), this);
    ui->menuBar->addAction(deco);
    deco->setVisible(false);

    connexion = new QAction(tr("&Connexion"), this);
    ui->menuBar->addAction(connexion);

    reg = new QAction(tr("&Register"), this);
    ui->menuBar->addAction(reg);

    QAction* refresh = new QAction(tr("&Refresh"), this);
    refresh->setIcon(QIcon(":/new/IconsHome/Icons/refresh.png"));
    ui->menuBar->addAction(refresh);

    ui->menuListe->menuAction()->setVisible(false);

    connect(connexion, SIGNAL(triggered(bool)), this, SLOT(on_connexionAction_triggered()));
    connect(deco, SIGNAL(triggered(bool)), this, SLOT(on_deconnexionAction_triggered()));
    connect(reg, SIGNAL(triggered(bool)), this, SLOT(on_registerAction_triggered()));
    connect(sharing, SIGNAL(triggered(bool)), this, SLOT(on_partageAction_triggered()));
    connect(refresh, SIGNAL(triggered(bool)), this, SLOT(on_refreshAction_triggered()));

    this->refresh();
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedCheck(int id){
    if(actualList->getItem(id)){
        actualList->getItem(id)->setCheck();
        repo.saveItem(actualList->getItem(id));
    }
    this->refresh();
}

void MainWindow::clickedPin(int id){
    if(actualList->getItem(id)){
        actualList->getItem(id)->setPin();
        repo.saveItem(actualList->getItem(id));
    }
    this->refresh();
}

void MainWindow::clickedFav(int id){
    if(actualList->getItem(id)){
        actualList->getItem(id)->setFav();
        repo.saveItem(actualList->getItem(id));
    }
    this->refresh();
}

void MainWindow::clickedImg(int id){

    Item* item = actualList->getItem(id);

    if(item){
        if(!item->image.isNull()){
            DisplayImageDialog imageDialog;
            imageDialog.setModal(true);
            imageDialog.setDelPermission(actualList->UserCanWrite(connectedUser->userID));
            imageDialog.setImage(item->image);

            if(imageDialog.exec() == 2){ //Delete image
                item->deleteImage();

                repo.saveItem(item);
                this->refresh();
            }
        }
        else{
            if(actualList->UserCanWrite(connectedUser->userID)){
                QMessageBox confirmationBox;
                confirmationBox.setText(QString("There is no image for this item, do you want to upload one now?"));
                confirmationBox.setInformativeText(actualList->getItem(id)->title);
                confirmationBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

                if(confirmationBox.exec() == QMessageBox::Yes){
                    QFileDialog uploadImage(this);
                    uploadImage.setNameFilter(tr("Images (*.png *.jpg *.jpeg)"));
                    uploadImage.setViewMode(QFileDialog::Detail);
                    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/", tr("Images (*.png *.jpg *.jpeg)"));
                    actualList->getItem(id)->image = QPixmap(fileName);

                    repo.saveItem(item);
                    this->refresh();
                }
            }
        }
    }
}

void MainWindow::clickedDel(int id){
    QMessageBox confirmationBox;
    confirmationBox.setText(QString("Are you sure you want to delete this item?"));
    confirmationBox.setInformativeText(actualList->getItem(id)->title);
    confirmationBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if(confirmationBox.exec() == QMessageBox::Ok){
        //actualList->listItem.erase(remove(actualList->listItem.begin(), actualList->listItem.end(), actualList->getItem(id)),actualList->listItem.end());
        if(actualList->getItem(id)){
            repo.deleteItem(actualList->getItem(id));
        }
    }

    this->refresh();
}

void MainWindow::refresh(){
    List* refreshedList = new List();

    if(connectedUser){
        listOfLists = repo.getListOfUser(connectedUser->userID);
    }
    else{
        listOfLists.clear();
    }

    this->showLists(listOfLists);

    if(actualList){
        for(int i=0; i<listOfLists.size(); i++){
            if(listOfLists[i]->listID == actualList->listID){
                refreshedList = listOfLists[i];
            }
        }
        actualList = refreshedList;

        if(actualList->listID == NULL){
            ui->btn_add_item->setDisabled(true);
        }

        this->showItems(actualList->listItem);
    }
}

void MainWindow::showList(QListWidgetItem* item){
    List* list = item->data(Qt::UserRole).value<List*>();
    actualList = list;

    this->showItems(list->listItem);

    ui->actionEdit->setVisible(list->UserIsOwner(connectedUser->userID));
    ui->actionDelete->setVisible(list->UserIsOwner(connectedUser->userID));
    ui->btn_add_item->setEnabled(list->UserCanWrite(connectedUser->userID));

    sharing->setVisible(list->UserCanWrite(connectedUser->userID));
}

void MainWindow::showLists(vector<List*> lists){

    ui->listLists->clear();

    for(int i = 0; i < lists.size(); i++){
        List* list = lists[i];

        QVariant qv;
        qv.setValue(list);

        QListWidgetItem * item = new QListWidgetItem;
        item->setText(list->description);

        item->setBackgroundColor(getQColorFromString(list->color.toStdString()));
        item->setData(Qt::UserRole,qv);
        ui->listLists->addItem(item);
    }
}

void MainWindow::showItems(vector<Item*> items){
    sort(items.begin(), items.end(), isImportant());

    QTableWidgetItem *tableItem = 0;
    int Icon_Size = 50;

    ui->listItemTable->clear();
    ui->listItemTable->horizontalHeader()->hide();
    ui->listItemTable->verticalHeader()->hide();
    ui->listItemTable->setShowGrid(false);
    ui->listItemTable->viewport()->setFocusPolicy(Qt::NoFocus);
    ui->listItemTable->setColumnCount(6);

    ui->listItemTable->setColumnWidth(0,25);
    ui->listItemTable->setColumnWidth(1,440);
    ui->listItemTable->setColumnWidth(2,40);
    ui->listItemTable->setColumnWidth(3,40);
    ui->listItemTable->setColumnWidth(4,40);
    ui->listItemTable->setColumnWidth(5,40);

    ui->listItemTable->setRowCount(items.size());

    for(int i=0; i<items.size();i++){
        Item* item = items[i];
        Qt::CheckState check = ((item->isChecked) ? Qt::Checked : Qt::Unchecked);
        Qt::CheckState pin = ((item->isPinned) ? Qt::Checked : Qt::Unchecked);
        Qt::CheckState important = ((item->isFavorite) ? Qt::Checked : Qt::Unchecked);

        QSignalMapper* signalMapperCheck;
        QSignalMapper* signalMapperPin;
        QSignalMapper* signalMapperFav;
        QSignalMapper* signalMapperImg;
        QSignalMapper* signalMapperDel;

        signalMapperCheck = new QSignalMapper(this);
        connect(signalMapperCheck, SIGNAL(mapped(int)), this, SLOT(clickedCheck(int)));

        signalMapperPin = new QSignalMapper(this);
        connect(signalMapperPin, SIGNAL(mapped(int)), this, SLOT(clickedPin(int)));

        signalMapperFav = new QSignalMapper(this);
        connect(signalMapperFav, SIGNAL(mapped(int)), this, SLOT(clickedFav(int)));

        signalMapperImg = new QSignalMapper(this);
        connect(signalMapperImg, SIGNAL(mapped(int)), this, SLOT(clickedImg(int)));

        signalMapperDel = new QSignalMapper(this);
        connect(signalMapperDel, SIGNAL(mapped(int)), this, SLOT(clickedDel(int)));

        QVariant qv;
        qv.setValue(item);

        /* Item Name */
        tableItem = new QTableWidgetItem(item->title);
        tableItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);


        /* CheckBox */
        QCheckBox* checkBoxItem = new QCheckBox();
        checkBoxItem->setCheckable(true);
        checkBoxItem->setCheckState(check);
        checkBoxItem->setEnabled(actualList->UserCanCheck(connectedUser->userID));

        signalMapperCheck->setMapping(checkBoxItem, item->itemID);
        connect(checkBoxItem, SIGNAL(clicked()), signalMapperCheck, SLOT(map()));


        /* Important Button */
        QPushButton* btn_important = new QPushButton();
        signalMapperFav->setMapping(btn_important, item->itemID);
        connect(btn_important, SIGNAL(clicked()), signalMapperFav, SLOT(map()));
        btn_important->setCheckable(true);
        btn_important->setChecked(important);
        btn_important->setEnabled(actualList->UserCanWrite(connectedUser->userID));

        QIcon ico_important;
        ico_important.addFile(":/new/IconsHome/Icons/important_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_important.addFile(":/new/IconsHome/Icons/important_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_important->setIcon(ico_important);
        btn_important->setFlat(true);
        btn_important->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; } QPushButton:disabled{}");


        /* Pin Button */
        QPushButton* btn_pin = new QPushButton();
        signalMapperPin->setMapping(btn_pin, item->itemID);
        connect(btn_pin, SIGNAL(clicked()), signalMapperPin, SLOT(map()));
        btn_pin->setCheckable(true);
        btn_pin->setChecked(pin);
        btn_pin->setEnabled(actualList->UserCanPin(connectedUser->userID));

        QIcon ico_pin;
        ico_pin.addFile(":/new/IconsHome/Icons/pin_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_pin.addFile(":/new/IconsHome/Icons/pin_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_pin->setIcon(ico_pin);
        btn_pin->setFlat(true);
        btn_pin->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Image Button */
        QPushButton* btn_image = new QPushButton();
        signalMapperImg->setMapping(btn_image, item->itemID);
        connect(btn_image, SIGNAL(clicked()), signalMapperImg, SLOT(map()));

        if(item->asImage()){
            btn_image->setIcon(QIcon(":/new/IconsHome/Icons/image_off.png"));
        }
        else{
            btn_image->setIcon(QIcon(":/new/IconsHome/Icons/image_on.png"));
        }

        btn_image->setFlat(true);
        btn_image->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Delete Button */
        QPushButton* btn_delete = new QPushButton();
        signalMapperDel->setMapping(btn_delete, item->itemID);
        connect(btn_delete, SIGNAL(clicked()), signalMapperDel, SLOT(map()));
        btn_delete->setChecked(Qt::Checked);
        btn_delete->setEnabled((actualList->UserCanDelete(connectedUser->userID) && item->isPinned == false) || actualList->UserIsOwner(connectedUser->userID));


        QIcon ico_delete;
        ico_delete.addFile(":/new/IconsHome/Icons/delete_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_delete.addFile(":/new/IconsHome/Icons/delete_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_delete->setIcon(ico_delete);
        btn_delete->setFlat(true);
        btn_delete->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Setting Widget In Table*/
        ui->listItemTable->setCellWidget(i,0,checkBoxItem);
        ui->listItemTable->setItem(i,1,tableItem);
        ui->listItemTable->setCellWidget(i,2,btn_pin);
        ui->listItemTable->setCellWidget(i,3,btn_important);
        ui->listItemTable->setCellWidget(i,4,btn_image);
        ui->listItemTable->setCellWidget(i,5,btn_delete);
    }

    ui->listItemTable->show();
}

void MainWindow::on_connexionAction_triggered()
{
    ConnectionDialog connection;
    connection.setModal(true);
    if(connection.exec()){
        //Add Connection System
        connectedUser = connection.getUser();
        connexion->setVisible(false);
        reg->setVisible(false);
        deco->setVisible(true);
        ui->menuListe->menuAction()->setVisible(true);
    }

    this->refresh();
}

void MainWindow::on_deconnexionAction_triggered()
{
    connectedUser = NULL;
    connexion->setVisible(true);
    reg->setVisible(true);
    deco->setVisible(false);
    sharing->setVisible(false);
    ui->menuListe->menuAction()->setVisible(true);

    this->refresh();
}

void MainWindow::on_registerAction_triggered()
{
    DialogRegister dialogRegister;
    dialogRegister.setModal(true);
    dialogRegister.exec();
}

void MainWindow::on_refreshAction_triggered()
{
    this->refresh();
}

void MainWindow::on_partageAction_triggered()
{
    SharingDialog sharing;
    sharing.setModal(true);
    sharing.setPermissions(actualList->listPermission, actualList->listID);
    sharing.exec();

    actualList->listPermission = sharing.getPermissions();
}

void MainWindow::on_actionNew_triggered()
{
    NewListDialog newListDialog;
    newListDialog.setModal(true);
    if(newListDialog.exec()){
        List* newList = newListDialog.getList();
        newList->userID = connectedUser->userID;
        repo.createList(newList);
        this->refresh();
    }
}

void MainWindow::on_actionDelete_triggered()
{
    QMessageBox confirmationBox;
    confirmationBox.setText(QString("Are you sure you want to delete this list?"));
    confirmationBox.setInformativeText(actualList->description);
    confirmationBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if(confirmationBox.exec() == QMessageBox::Ok){
        listOfLists.erase(remove(listOfLists.begin(), listOfLists.end(), actualList),listOfLists.end());
        repo.deleteList(actualList);
    }

    this->refresh();
}

void MainWindow::on_actionEdit_triggered()
{
    NewListDialog editListDialog;
    editListDialog.setModal(true);
    editListDialog.setData(actualList);
    if(editListDialog.exec()){
        List* editedList = editListDialog.getList();

        actualList->description = editedList->description;
        actualList->color = editedList->color;

        repo.saveList(actualList);

        this->refresh();
    }
}

void MainWindow::on_btn_add_item_clicked()
{
    AddItemDialog itemDialog;
    itemDialog.setModal(true);
    if(itemDialog.exec()){
        Item* newItem = itemDialog.getItem();
        newItem->listID = actualList->listID;
        newItem->userID = connectedUser->userID;
        repo.createItem(newItem);
        this->refresh();
    }
}
