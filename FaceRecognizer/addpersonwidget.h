#ifndef ADDPERSONWIDGET_H
#define ADDPERSONWIDGET_H

#include <QDialog>

namespace Ui {
class AddPersonWidget;
}

class AddPersonWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddPersonWidget(QWidget *parent = 0);
    ~AddPersonWidget();
    
private:
    Ui::AddPersonWidget *ui;
};

#endif // ADDPERSONWIDGET_H
