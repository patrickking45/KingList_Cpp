#ifndef SHARINGDIALOG_H
#define SHARINGDIALOG_H

#include <QDialog>
#include <permission.h>

using namespace std;

namespace Ui {
class SharingDialog;
}

class SharingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SharingDialog(QWidget *parent = 0);
    ~SharingDialog();
    void setPermissions(vector<Permission*>);
    void showShares();

public slots:
    void clickedCheck(int buttonId);
    void clickedWrite(int buttonId);
    void clickedDelete(int buttonId);
    void clickedShare(int buttonId);
    void clickedUnShare(int buttonId);

private:
    Ui::SharingDialog *ui;
};

#endif // SHARINGDIALOG_H