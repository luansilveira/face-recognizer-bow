#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>


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

private slots:
    void on_selectImagesButton_clicked();


    void on_new_person_toggled(bool checked);

private:
    Ui::AddPersonDialog *ui;

    QStringList filenames_;

    bool new_person;
    int id;
    std::string name;

};

#endif // ADDPERSONDIALOG_H
