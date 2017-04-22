#include "additemdialog.h"
#include "ui_additemdialog.h"

AddItemDialog::AddItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

Item* AddItemDialog::getItem(){
    return new Item(155541, 154887, ui->itemTitle->text().toStdString(), QDate(2017,04,18), QDate(2017,04,18), false, QDate(1,1,1), false, false, false);
}

void AddItemDialog::on_pushButton_2_clicked()
{
    this->done(0);
}

void AddItemDialog::on_btn_save_clicked()
{
    this->done(1);
}
