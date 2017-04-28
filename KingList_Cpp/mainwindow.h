#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <model_liste.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showLists(vector<List*>);
    void showItems(vector<Item*>);
    void refresh();

public slots:
    void showList(QListWidgetItem*);
    void clickedCheck(int buttonId);
    void clickedPin(int buttonId);
    void clickedFav(int buttonId);
    void clickedImg(int buttonId);
    void clickedDel(int buttonId);
    void on_connexionAction_triggered();
    void on_registerAction_triggered();
    void on_deconnexionAction_triggered();
    void on_partageAction_triggered();
    void on_refreshAction_triggered();

private slots:
    void on_actionNew_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_triggered();

    void on_btn_add_item_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
