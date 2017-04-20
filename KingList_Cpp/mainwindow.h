#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showLists();

public slots:
    void showList(QListWidgetItem*);
    void clickedPin(int buttonId);
    void clickedFav(int buttonId);
    void clickedImg(int buttonId);
    void clickedDel(int buttonId);
    void on_deconnexionAction_triggered();
    void on_refreshAction_triggered();

private slots:
    void on_actionNew_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
