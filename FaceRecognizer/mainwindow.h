#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <addpersondialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void loadImages(QStringList &filenames);
private slots:

    void on_addNewPerson_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
