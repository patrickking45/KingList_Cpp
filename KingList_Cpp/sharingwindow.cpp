#include "sharingwindow.h"
#include "ui_sharingwindow.h"

SharingWindow::SharingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SharingWindow)
{
    ui->setupUi(this);
}

SharingWindow::~SharingWindow()
{
    delete ui;
}
