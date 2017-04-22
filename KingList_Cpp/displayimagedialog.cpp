#include "displayimagedialog.h"
#include "ui_displayimagedialog.h"

#include <QMessageBox>

DisplayImageDialog::DisplayImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayImageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Display Image");
}

DisplayImageDialog::~DisplayImageDialog()
{
    delete ui;
}

void DisplayImageDialog::setImage(QPixmap image){
    this->setFixedSize(image.size());
    this->setFixedHeight(image.height() + 15);
    ui->displayImage->setBaseSize(image.size());
    ui->displayImage->setPixmap(image);
}

void DisplayImageDialog::on_pushButton_clicked()
{
    QMessageBox confirmationBox;
    confirmationBox.setText(QString("Are you sure you want to delete this image?"));
    confirmationBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if(confirmationBox.exec() == QMessageBox::Ok){
        this->done(2);
    }
}
