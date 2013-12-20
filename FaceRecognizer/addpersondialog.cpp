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

void AddPersonDialog::setExistingNames(std::vector<std::string> names)
{
    for(int i=0;i<names.size();i++){
        ui->existingNames->addItem(QString::fromStdString(names[i]));
    }

}

int AddPersonDialog::getID()
{
    return id_;
}


std::string AddPersonDialog::getName()
{
    return name_;
}

bool AddPersonDialog::isNewPerson()
{
    return new_person_;
}

QStringList AddPersonDialog::getFilenames()
{
    return filenames_;
}



void AddPersonDialog::on_new_person_toggled(bool checked)
{
    new_person_ = checked;

    std::cout << "Entrou na new person toggled . state = " << new_person_ << std::endl;
    //! \todo CONFERIR ESSA FUNÇÃO. TÁ SETANDO ERRADO
}

void AddPersonDialog::on_AddPersonDialog_finished(int result)
{

    if(new_person_)
    {
        name_ = ui->name_new_person->text().toStdString();
    }else
    {
        id_ = ui->existingNames->currentIndex();
        name_ = ui->existingNames->currentText().toStdString();
    }
}

void AddPersonDialog::on_radioButton_2_toggled(bool checked)
{
    new_person_ = !checked;
}
