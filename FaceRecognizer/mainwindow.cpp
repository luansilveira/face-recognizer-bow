#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addNewPerson_clicked()
{
    AddPersonDialog addPersonDialog(this);
    int id;

    std::vector<std::string> names;
    people.getNames(names);
    addPersonDialog.setExistingNames(names);

    if (addPersonDialog.exec())
    {
        QStringList filenames = addPersonDialog.getFilenames();

        if(addPersonDialog.isNewPerson())
        {
            id = people.addNewPerson(addPersonDialog.getName());
            ui->log->append("Person created. Name = " + QString::fromStdString(addPersonDialog.getName()));
        }
        else
        {
            id = addPersonDialog.getID();
        }
        foreach (QString filename, filenames) {
            people.addImage(id,filename.toStdString());
            ui->log->append("Image " + filename + " added");
        }
    }
    else
    {
        ui->log->append("No image selected");
    }


}
