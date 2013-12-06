#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include <QFileDialog>

AddPersonDialog::AddPersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

void AddPersonDialog::on_selectImagesButton_clicked()
{
    filenames_ = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.png *.xpm *.jpg)");

}

QStringList AddPersonDialog::getFilenames()
{
    return filenames_;
}



void AddPersonDialog::on_new_person_toggled(bool checked)
{
    new_person = checked;


}
