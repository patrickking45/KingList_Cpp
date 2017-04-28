#ifndef DIALOGREGISTER_H
#define DIALOGREGISTER_H

#include <QDialog>
#include "model_user.h"

namespace Ui {
class DialogRegister;
}

class DialogRegister : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRegister(QWidget *parent = 0);
    ~DialogRegister();

private slots:
    void on_btn_register_clicked();

private:
    Ui::DialogRegister *ui;
};

#endif // DIALOGREGISTER_H
