#include "thired.h"
#include "ui_thired.h"

thired::thired(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thired)
{
    ui->setupUi(this);
}

thired::~thired()
{
    delete ui;
}
QRadioButton* thired::getread(){
    return ui->radioread_2;
}

QRadioButton* thired::getwrite(){
    return ui->radiowrite_2;
}

QPushButton* thired::subbut(){
    return ui->subbut_2;
}
QLineEdit* thired::getjicunvalue(){
return ui->jicunvalue_2;
}

void thired::on_exitbut_2_clicked()
{
    this->hide();
}
