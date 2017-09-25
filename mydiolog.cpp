#include "mydiolog.h"
#include "ui_mydiolog.h"

Mydiolog::Mydiolog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mydiolog)
{
    ui->setupUi(this);
}

Mydiolog::~Mydiolog()
{
    delete ui;
}
