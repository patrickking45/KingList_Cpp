#include "newlistdialog.h"
#include "ui_newlistdialog.h"
#include "liste.h"

NewListDialog::NewListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewListDialog)
{
    ui->setupUi(this);
}

NewListDialog::~NewListDialog()
{
    delete ui;
}

List* NewListDialog::getList(){
    return (new List(101,ui->txt_desc->text().toStdString(), ui->txt_color->text().toStdString()));
}

void NewListDialog::on_pushButton_clicked()
{
    this->done(1);
}

void NewListDialog::on_pushButton_2_clicked()
{
    this->close();
}
