#ifndef SHARINGWINDOW_H
#define SHARINGWINDOW_H

#include <QDialog>

namespace Ui {
class SharingWindow;
}

class SharingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SharingWindow(QWidget *parent = 0);
    ~SharingWindow();

private:
    Ui::SharingWindow *ui;
};

#endif // SHARINGWINDOW_H
