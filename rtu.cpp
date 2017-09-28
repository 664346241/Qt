#include "rtu.h"
#include "ui_rtu.h"
#include"mainwindow.h"

RTU::RTU(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RTU)
{
    my_xieyi=My_modbus;
    ui->setupUi(this);
    mydialog=new thired;
    mydialog->hide();
  //  ui->textEdit->installEventFilter(this);



    QObject::connect(ui->action_all,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()) );
    QObject::connect(ui->action_copy,SIGNAL(triggered()),ui->textEdit,SLOT(copy()) );
    QObject::connect(ui->action_zhantie,SIGNAL(triggered()),ui->textEdit,SLOT(paste()) );
    QObject::connect(ui->action_Refresh,SIGNAL(triggered()),ui->textEdit,SLOT(redo()) );
    QObject::connect(ui->action_jianqie,SIGNAL(triggered()),ui->textEdit,SLOT(cut()) );
    QObject::connect(ui->actionchexiao,SIGNAL(triggered()),ui->textEdit,SLOT(undo()) );
    QObject::connect(ui->action_Date,SIGNAL(triggered()),this,SLOT(my_date()) );
    QObject::connect(ui->action_G,SIGNAL(triggered()),this,SLOT(my_setFont()) );
    QObject::connect(ui->actionTemp_T,SIGNAL(triggered()),this,SLOT(my_temp()));
    QObject::connect(ui->action_query,SIGNAL(triggered()),this,SLOT(my_read()) );
    QObject::connect(ui->action_write,SIGNAL(triggered()),this,SLOT(my_write()));
    QObject::connect(ui->actionExit_Q,SIGNAL(triggered()),this,SLOT(close()) );

    qDebug()<<QString("old myrtu");


}


RTU::~RTU()
{
    delete ui;
}


 QListWidget* RTU::gethistoryWidget(){
     return ui->historyitem;
 }

QTextEdit* RTU::getinputlineedit(){
    return ui->textEdit;

}

QAction* RTU::getactionret(){
    return ui->action_ret;
}
QPushButton* RTU::getsubtut(){
    return ui->subbut;
}

QPushButton* RTU::getendbut(){
    return ui->endbut;
}

QPushButton* RTU::getbegbut(){
return ui->begbut;
}

QListWidget* RTU::getshowlistwidget(){
return ui->recevelist;

}
/*
//函数，它是一个虚函数，权限设置为protected。
bool RTU::eventFilter(QObject *obj, QEvent *e)
{
    Q_ASSERT(obj == ui->textEdit);
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *event = static_cast<QKeyEvent*>(e);
        if (event->key() == Qt::Key_Return && (event->modifiers() & Qt::ControlModifier))
        {
           // sendMsg(); //发送消息的槽
            on_pushButton_clicked();
            return true;
        }
    }
    return false;
}
*/
void RTU::my_read(){

    mydialog->show();
    this->mydialog->getread()->setChecked(1);
    this->mydialog->getjicunvalue()->setEnabled(0);

}

void RTU::my_write(){
  //  mydialog=new Mydiolog;
    mydialog->show();
     this->mydialog->getwrite()->setChecked(1);
    this->mydialog->getjicunvalue()->setEnabled(1);



}

void RTU::my_temp(){

   QString now=QDir::tempPath();
   ui->textEdit->append(now);
   now=QDir::rootPath();
   ui->textEdit->append(now);
   now=QDir::homePath();
   ui->textEdit->append(now);

}
void RTU::my_date(){
    QDateTime current= QDateTime::currentDateTime();
    QString now=current.toString("yyyy-MM-dd hh-mm-ss");
    ui->textEdit->append(now);
    ui->recevelist->addItem(new QListWidgetItem(now) );
 //   ui->recevelist->append(now);

}
void RTU::my_setFont(){

    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
    if (ok) {
       ui->textEdit->setFont(font);
    } else {
        QMessageBox::information(this,"error","setting error");
    }

}
/*
void RTU::on_pushButton_clicked()
{
QString temp=ui->textEdit->toPlainText();
QListWidgetItem *item=new  QListWidgetItem;
item->setText(temp);
ui->historyitem->addItem(item);
ui->textEdit->clear();
ui->textEdit->setFocus();
}*/
void RTU::my_exit(){
    this->close();
}




void RTU::on_subbut_clicked()
{

}
