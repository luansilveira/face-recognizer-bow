#include "addpersonwidget.h"
#include "ui_addpersonwidget.h"

AddPersonWidget::AddPersonWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonWidget)
{
    ui->setupUi(this);
}

AddPersonWidget::~AddPersonWidget()
{
    delete ui;
}
