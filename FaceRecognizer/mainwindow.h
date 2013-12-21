#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <addpersondialog.h>
#include "people.h"
#include <bag_of_words.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_addNewPerson_clicked();

    void on_trainDatabase_clicked();

    
    void on_testImages_clicked();

    void on_storeDatabase_clicked();

    void on_loadDatabase_clicked();

    void on_addTestImages_clicked();

    void on_showDatabase_clicked();



private:
    Ui::MainWindow *ui;

    People people;
};

#endif // MAINWINDOW_H
