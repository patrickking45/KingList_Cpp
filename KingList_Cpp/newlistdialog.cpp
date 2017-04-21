#include "newlistdialog.h"
#include "ui_newlistdialog.h"
#include "liste.h"

#include <QColorDialog>


QColor buttonColor;
string colorRGB;


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
    return (new List(101,ui->txt_desc->text().toStdString(), colorRGB));
}

void NewListDialog::setData(List* list){
    colorRGB = list->color;
    vector<string> rgb = split(colorRGB, ",");
    buttonColor = QColor(stoi(rgb[0]),stoi(rgb[1]),stoi(rgb[2]),255);

    ui->txt_desc->setText(QString::fromStdString(list->description));
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
    colorRGB = to_string(buttonColor.red()) + ", " + to_string(buttonColor.green()) + ", " + to_string(buttonColor.blue());
    ui->colorPicker->setStyleSheet(QString::fromStdString("QPushButton {background-color: rgb(" + colorRGB + ")}"));
}
