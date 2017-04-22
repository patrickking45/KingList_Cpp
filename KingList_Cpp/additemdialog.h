#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <item.h>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemDialog(QWidget *parent = 0);
    ~AddItemDialog();
    Item* getItem();

private slots:
    void on_pushButton_2_clicked();

    void on_btn_save_clicked();

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
