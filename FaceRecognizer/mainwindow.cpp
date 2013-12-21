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
            ui->log->append("Person created. Name = " + QString::fromStdString(addPersonDialog.getName()) +
                            " ID = " + QString::number(id));
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

void MainWindow::on_trainDatabase_clicked()
{

    people.trainDatabase();

}


void MainWindow::on_testImages_clicked()
{

    people.testImages();

}

void MainWindow::on_storeDatabase_clicked()
{
    cv::FileStorage fs("database.xml", cv::FileStorage::WRITE);

    fs << "people" << people;

    fs.release();

    ui->log->append("Write database in database.xml");
}

void MainWindow::on_loadDatabase_clicked()
{
    cv::FileStorage fs("database.xml", cv::FileStorage::READ);

    if (!fs.isOpened())
    {
        ui->log->append("Failed to open dabatase.xml");
    }
    else
    {
        fs["people"] >> people;

        people.setLog(ui->log);

        fs.release();

        ui->log->append("Read database from database.xml");

    }

}

void MainWindow::on_addTestImages_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                "Select one or more files to open",
                "/home/lsilveira/Codigos/face-recognizer-bow/FaceRecognizer/Datasets",
                "Images (*.png *.xpm *.jpg *.pgm)");

    BOOST_FOREACH(QString filename,filenames)
    {
        people.addTestImages(filename.toStdString());

    }
}

void MainWindow::on_showDatabase_clicked()
{
    people.showDatabase();
}
