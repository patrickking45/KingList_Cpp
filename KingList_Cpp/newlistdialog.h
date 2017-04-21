#ifndef NEWLISTDIALOG_H
#define NEWLISTDIALOG_H

#include <QDialog>
#include <liste.h>

namespace Ui {
class NewListDialog;
}

class NewListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewListDialog(QWidget *parent = 0);
    ~NewListDialog();

    List* getList();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NewListDialog *ui;
};

#endif // NEWLISTDIALOG_H