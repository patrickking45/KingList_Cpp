#include "dialog_displayimage.h"
#include "ui_dialog_displayimage.h"

#include <QMessageBox>

DisplayImageDialog::DisplayImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayImageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Display Image");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowIcon(QIcon(":/new/Logo/Icons/Logo/KingList-Logo.png"));
}

DisplayImageDialog::~DisplayImageDialog()
{
    delete ui;
}

void DisplayImageDialog::setDelPermission(bool delPermission){
    ui->pushButton->setEnabled(delPermission);
}

void DisplayImageDialog::setImage(QPixmap image){
    this->setFixedSize(image.size());
    this->setFixedHeight(image.height() + 15);
    ui->displayImage->setFixedSize(image.size());
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
