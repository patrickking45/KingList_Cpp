#include "dialog_additem.h"
#include "ui_dialog_additem.h"

AddItemDialog::AddItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("Add Item");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

Item* AddItemDialog::getItem(){
    return new Item(0, 0, ui->itemTitle->text(), QDate::currentDate(), QDate(1,1,1), false, QDate(1,1,1), false, false, false);
}

void AddItemDialog::on_pushButton_2_clicked()
{
    this->done(0);
}

void AddItemDialog::on_btn_save_clicked()
{
    this->done(1);
}
