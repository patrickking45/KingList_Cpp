#ifndef INVITEDIALOG_H
#define INVITEDIALOG_H

#include <QDialog>
#include <model_permission.h>

namespace Ui {
class InviteDialog;
}

class InviteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InviteDialog(QWidget *parent = 0);
    ~InviteDialog();
    Permission* getPermission();
    Permission* newPermission;

private slots:
    void on_btn_cancel_clicked();

    void on_btn_share_clicked();

private:
    Ui::InviteDialog *ui;
};

#endif // INVITEDIALOG_H
