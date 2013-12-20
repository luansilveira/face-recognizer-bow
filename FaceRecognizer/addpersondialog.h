#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
#include <iostream>

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddPersonDialog(QWidget *parent = 0);
    ~AddPersonDialog();
    
    QStringList getFilenames();

    int getID();
    std::string getName();

    bool isNewPerson();



    void setExistingNames(std::vector<std::string> names);

private slots:
    void on_selectImagesButton_clicked();


    void on_new_person_toggled(bool checked);

    void on_AddPersonDialog_finished(int result);

    void on_radioButton_2_toggled(bool checked);

private:
    Ui::AddPersonDialog *ui;

    QStringList filenames_;

    bool new_person_;
    int id_;
    std::string name_;

};

#endif // ADDPERSONDIALOG_H
