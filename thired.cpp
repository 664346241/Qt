#include "thired.h"
#include "ui_thired.h"

thired::thired(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thired)
{
    ui->setupUi(this);
    connect(ui->radioread_2,SIGNAL(toggled(bool)),this,SLOT(changeMyValue()));
    connect(ui->radioread_2,SIGNAL(toggled(bool)),this,SLOT(changeMyValue()));
    QRegExp regx("[0-9a-fA-F]{1,2}");
   QValidator *validator = new QRegExpValidator(regx, ui->machineaddress_2 );
   ui->machineaddress_2->setValidator( validator );
   QRegExp regx2("[0-9a-fA-F]{1,4}");
   QValidator *validator2 = new QRegExpValidator(regx2, ui->address_2 );
   ui->address_2->setValidator( validator2 );
   QValidator *validator3 = new QRegExpValidator(regx2, ui->addresslenth_2 );
   ui->addresslenth_2->setValidator( validator3 );
}
void thired::changeMyValue(){
    if(ui->radioread_2->isChecked()){

        this->ui->jicunvalue_2->setEnabled(0);
    }else{

        this->ui->jicunvalue_2->setEnabled(1);
    }


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


QRadioButton* thired::getradioread(){
    return ui->radioread_2;
}

QLineEdit* thired::getmachineaddress(){
    return ui->machineaddress_2;
}

QLineEdit* thired::getaddress()
{
    return ui->address_2;
}

QLineEdit* thired::getaddresslenth(){
    return ui->addresslenth_2;
}

QPushButton* thired::getsubmit(){
    return ui->subbut_2;
}
