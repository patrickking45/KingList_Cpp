#ifndef DISPLAYIMAGEDIALOG_H
#define DISPLAYIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class DisplayImageDialog;
}

class DisplayImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayImageDialog(QWidget *parent = 0);
    ~DisplayImageDialog();
    void setImage(QPixmap);
    void setDelPermission(bool);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DisplayImageDialog *ui;
};

#endif // DISPLAYIMAGEDIALOG_H
