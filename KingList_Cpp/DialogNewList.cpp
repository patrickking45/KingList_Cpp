#include "dialog_newlist.h"
#include "ui_dialog_newlist.h"
#include "model_liste.h"
#include "utility.cpp"

#include <QColorDialog>


QColor buttonColor = QColor(Qt::white);
string colorRGB;

NewListDialog::NewListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewListDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
    this->setWindowTitle("Add list");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));
}

NewListDialog::~NewListDialog()
{
    delete ui;
}

List* NewListDialog::getList(){
    if(colorRGB == ""){colorRGB = "255,255,255";}
    return (new List(101,ui->txt_desc->text(), QString::fromStdString(colorRGB)));
}

void NewListDialog::setData(List* list){
    colorRGB = list->color.toStdString();
    buttonColor = getQColorFromString(colorRGB);

    ui->txt_desc->setText(list->description);
    ui->colorPicker->setStyleSheet(QString::fromStdString("QPushButton {background-color: rgb(" +colorRGB+ ")}"));
}

void NewListDialog::on_pushButton_clicked()
{
    this->done(1);
}

void NewListDialog::on_pushButton_2_clicked()
{
    this->close();
}

void NewListDialog::on_colorPicker_clicked()
{
    buttonColor = QColorDialog::getColor(buttonColor, this);
    colorRGB = getRGBStringFromQColor(buttonColor);
    ui->colorPicker->setStyleSheet(QString::fromStdString("QPushButton {background-color: rgb(" + colorRGB + ")}"));
}
