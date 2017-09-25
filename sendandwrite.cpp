#include "sendandwrite.h"
#include "ui_sendandwrite.h"

Sendandwrite::Sendandwrite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sendandwrite)
{
    ui->setupUi(this);
}

Sendandwrite::~Sendandwrite()
{
    delete ui;
}
