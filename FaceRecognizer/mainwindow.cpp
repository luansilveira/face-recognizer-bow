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

void MainWindow::loadImages(QStringList &filenames)
{

}

void MainWindow::on_addNewPerson_clicked()
{
    AddPersonDialog addPersonDialog(this);

    if (addPersonDialog.exec())
    {
        QStringList filenames = addPersonDialog.getFilenames();
        loadImages(filenames);
        //Adiciona a pessoa ao banco de dados

        foreach (QString filename, filenames) {
            ui->log->append("Adicionou a imagem " + filename);
        }

    }
    else
    {
        ui->log->append("Nenhuma Imagem selecionada");
    }


}
