#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "liste.h"
#include <QSignalMapper>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <newlistdialog.h>
#include <sharingdialog.h>
#include <additemdialog.h>
#include <displayimagedialog.h>

using namespace std;

List* actualList;
static vector<List*> listOfLists;
QAction* sharing;

struct isImportant{
    inline bool operator() (const Item* item1, const Item* item2){
        return (item1->isFavorite > item2->isFavorite);
    }
};

inline vector<string> split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

vector<List*> testInit(){

    listOfLists.clear();

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

    listOfLists.push_back(new List(1,1,items,permissions,"96,69,42","Épicerie",QDate(2017,04,18),QDate(1,1,1), false));

    items.clear();
    items.push_back(new Item(21, 154887, "John Wick 2", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, false, true));
    items.push_back(new Item(22, 154887, "Guardians of The Galaxy 2", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, true, false));
    items.push_back(new Item(23, 154887, "Thor: Ragnarok", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, true));
    items.push_back(new Item(24, 154887, "Histoire de Jouet 3", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, false, false));

    permissions.clear();
    permissions.push_back(new Permission(334, 103, true, true, false, true));
    permissions.push_back(new Permission(335, 104, true, false, true, true));
    permissions.push_back(new Permission(336, 115, true, false, false, false));

    listOfLists.push_back(new List(2,2,items,permissions,"255,250,240","Films",QDate(2017,04,18),QDate(1,1,1), false));

    items.clear();
    items.push_back(new Item(31, 154887, "Android", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, false, false));
    items.push_back(new Item(32, 154887, "Linux", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, false));
    items.push_back(new Item(33, 154887, "C++", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, true, false));
    items.push_back(new Item(34, 154887, "Angular", QDate(2017,04,18), QDate(1,1,1), false, QDate(1,1,1), false, false, true));
    items.push_back(new Item(35, 154887, "Java EE", QDate(2017,04,18), QDate(2017,04,18), true, QDate(1,1,1), false, true, false));

    permissions.clear();

    listOfLists.push_back(new List(3,3,items,permissions,"200,169,113","Devoir",QDate(2017,04,18),QDate(1,1,1), false));

    items.clear();

    permissions.clear();

    listOfLists.push_back(new List(4,4,items,permissions,"100,150,225","To Do",QDate(2017,04,18),QDate(1,1,1), false));

    return listOfLists;

}

vector<List*> getUserLists(){
    //Call WebServices
    return testInit();
}

List* getListById(int id){
    for(int i = 0 ; i < listOfLists.size(); i++){
        if(listOfLists[i]->listID == id){
            cout << listOfLists[i]->description << endl;
            return listOfLists[i];
        }
    }
    return NULL;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
    ui->setupUi(this);

    //Adding Actions
    sharing = new QAction(tr("&Partage"), this);
    sharing->setVisible(false);
    ui->menuBar->addAction(sharing);

    QAction* deco = new QAction(tr("&Déconnexion"), this);
    ui->menuBar->addAction(deco);

    QAction* refresh = new QAction(tr("&Refresh"), this);
    refresh->setIcon(QIcon(":/new/IconsHome/Icons/refresh.png"));
    ui->menuBar->addAction(refresh);

    connect(deco, SIGNAL(triggered(bool)), this, SLOT(on_deconnexionAction_triggered()));
    connect(sharing, SIGNAL(triggered(bool)), this, SLOT(on_partageAction_triggered()));
    connect(refresh, SIGNAL(triggered(bool)), this, SLOT(on_refreshAction_triggered()));

    vector<List*> initLists = getUserLists();

    this->showLists(initLists);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickedCheck(int id){
    cout << "Clicked Check :" << actualList->getItem(id)->title << endl;
    actualList->getItem(id)->setCheck();
}

void MainWindow::clickedPin(int id){
    cout << "Clicked Pin :" << actualList->getItem(id)->title << endl;
    actualList->getItem(id)->setPin();
}

void MainWindow::clickedFav(int id){
    cout << "Clicked Fav :" << actualList->getItem(id)->title << endl;
    actualList->getItem(id)->setFav();
    this->refresh();
}

void MainWindow::clickedImg(int id){

    Item* item = actualList->getItem(id);

    if(!item->image.isNull()){
        DisplayImageDialog imageDialog;
        imageDialog.setModal(true);
        imageDialog.setImage(item->image);
        if(imageDialog.exec() == 2){
            item->image = QPixmap();
            this->refresh();
        }
    }
    else{
        QFileDialog uploadImage(this);
        uploadImage.setNameFilter(tr("Images (*.png *.jpg *.jpeg)"));
        uploadImage.setViewMode(QFileDialog::Detail);
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/", tr("Images (*.png *.jpg *.jpeg)"));
        actualList->getItem(id)->image = QPixmap(fileName);

        this->refresh();
    }
}

void MainWindow::clickedDel(int id){
    QMessageBox confirmationBox;
    confirmationBox.setText(QString("Are you sure you want to delete this item?"));
    confirmationBox.setInformativeText(QString::fromStdString(actualList->getItem(id)->title));
    confirmationBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if(confirmationBox.exec() == QMessageBox::Ok){
        actualList->listItem.erase(remove(actualList->listItem.begin(), actualList->listItem.end(), actualList->getItem(id)),actualList->listItem.end());
    }

    this->refresh();
}

void MainWindow::refresh(){
    List* refreshedList = new List();

    this->showLists(listOfLists);

    if(actualList){
        for(int i=0; i<listOfLists.size(); i++){
            if(listOfLists[i]->listID == actualList->listID){
                refreshedList = listOfLists[i];
            }
        }
        actualList = refreshedList;

        this->showItems(actualList->listItem);
    }
}

void MainWindow::showList(QListWidgetItem* item){
    List* list = item->data(Qt::UserRole).value<List*>();
    this->showItems(list->listItem);

    actualList = list;
    ui->actionEdit->setVisible(true);
    ui->actionDelete->setVisible(true);
    sharing->setVisible(true );
}

void MainWindow::showLists(vector<List*> lists){

    ui->listLists->clear();

    for(int i = 0; i < lists.size(); i++){
        List* list = lists[i];

        QVariant qv;
        qv.setValue(list);

        QListWidgetItem * item = new QListWidgetItem;
        item->setText(QString::fromStdString(list->description));
        vector<string> rgb = split(list->color,",");
        item->setBackgroundColor(QColor(stoi(rgb[0]),stoi(rgb[1]),stoi(rgb[2]),255));
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
        tableItem = new QTableWidgetItem(QString::fromStdString(item->title));

        /* CheckBox */

        QCheckBox* checkBoxItem = new QCheckBox();
        checkBoxItem->setCheckState(check);
        signalMapperCheck->setMapping(checkBoxItem, item->itemID);
        connect(checkBoxItem, SIGNAL(clicked()), signalMapperCheck, SLOT(map()));


        /* Important Button */
        QPushButton* btn_important = new QPushButton();
        signalMapperFav->setMapping(btn_important, item->itemID);
        connect(btn_important, SIGNAL(clicked()), signalMapperFav, SLOT(map()));
        btn_important->setCheckable(true);
        btn_important->setChecked(important);

        QIcon ico_important;
        ico_important.addFile(":/new/IconsHome/Icons/important_on.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::On);
        ico_important.addFile(":/new/IconsHome/Icons/important_off.png",QSize(Icon_Size,Icon_Size),QIcon::Normal,QIcon::Off);

        btn_important->setIcon(ico_important);
        btn_important->setFlat(true);
        btn_important->setStyleSheet("QPushButton:checked { background:none; border: none; } QPushButton:pressed { background:none; border: none; }");


        /* Pin Button */
        QPushButton* btn_pin = new QPushButton();
        signalMapperPin->setMapping(btn_pin, item->itemID);
        connect(btn_pin, SIGNAL(clicked()), signalMapperPin, SLOT(map()));
        btn_pin->setCheckable(true);
        btn_pin->setChecked(pin);

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

        if(item->image.isNull()){
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
        btn_delete->setChecked(true);

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

void MainWindow::on_deconnexionAction_triggered()
{
    cout << "Déconnexion" << endl;
}

void MainWindow::on_refreshAction_triggered()
{
    this->refresh();
}

void MainWindow::on_partageAction_triggered()
{
    SharingDialog sharing;
    sharing.setModal(true);
    sharing.setPermissions(actualList->listPermission);
    sharing.exec();

    actualList->listPermission = sharing.getPermissions();
}

void MainWindow::on_actionNew_triggered()
{
    NewListDialog newListDialog;
    newListDialog.setModal(true);
    if(newListDialog.exec()){
        List* newList = newListDialog.getList();
        listOfLists.push_back(newList);
        this->refresh();
    }
}

void MainWindow::on_actionDelete_triggered()
{
    QMessageBox confirmationBox;
    confirmationBox.setText(QString("Are you sure you want to delete this list?"));
    confirmationBox.setInformativeText(QString::fromStdString(actualList->description));
    confirmationBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if(confirmationBox.exec() == QMessageBox::Ok){
        listOfLists.erase(remove(listOfLists.begin(), listOfLists.end(), actualList),listOfLists.end());
    }

    this->refresh();
}

void MainWindow::on_actionEdit_triggered()
{
    NewListDialog editListDialog;
    editListDialog.setModal(true);
    editListDialog.setData(actualList);
    if(editListDialog.exec()){
        List* editingList = getListById(actualList->listID);
        List* editedList = editListDialog.getList();

        editingList->description = editedList->description;
        editingList->color = editedList->color;

        this->refresh();
    }
}

void MainWindow::on_btn_add_item_clicked()
{
    AddItemDialog itemDialog;
    itemDialog.setModal(true);
    if(itemDialog.exec()){
        Item* newItem = itemDialog.getItem();
        actualList->listItem.push_back(newItem);
        this->refresh();
    }
}
