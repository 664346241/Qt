﻿#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     mytimer=new QTimer;
    ui->setupUi(this);
    r=new RTU;
    this->setWindowTitle("termiros setting");
    QObject::connect(ui->actionSave_S,SIGNAL(triggered()),this,SLOT(saveasfile()) );
    QObject::connect(ui->actionExit_q,SIGNAL(triggered()),this,SLOT(my_exits()) );
    QObject::connect(ui->actionOpen_O,SIGNAL(triggered()),this,SLOT(my_open()) );
    QObject::connect(ui->actionSaves,SIGNAL(triggered()),this,SLOT(my_saves()) );

    QObject::connect(this->r->getactionret(),SIGNAL(triggered()),this,SLOT(myDisPlay()));
    QObject::connect(this->r->getbegbut(),SIGNAL(clicked()),this,SLOT(mybegin()));
    QObject::connect(this->r->getendbut(),SIGNAL(clicked()),this,SLOT(mystop()));

    QObject::connect(this->mytimer,SIGNAL(timeout()),this,SLOT(ontimeout()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    int speed_arr[] = {9600,38400, 19200, 4800, 2400, 1200, 300};
    QString MyTermiosName=ui->twrmiosnameinput->text();//名字
    int PortRate=speed_arr[ui->portrate->currentIndex()];//频率
    int datanum=ui->datanum->currentText().toInt();//数据位
    int stopnum=0;//停止位
    if(this->ui->radiostop1->isChecked())
        stopnum=1;
    if(this->ui->radiostop2->isChecked())
        stopnum=2;
    qDebug()<<stopnum;
    bufflen=0;
    fd = OpenDev(MyTermiosName.trimmed().toStdString().c_str()); //打开串口
    if (fd > 0) {
        struct termios Opt;
        tcgetattr(fd, &Opt);

        tcflush(fd, TCIOFLUSH);
        cfsetispeed(&Opt, PortRate);
        cfsetospeed(&Opt, PortRate);
        if (tcsetattr(fd, TCSANOW, &Opt)!= 0) {
             QMessageBox::information(this,"termiros info","Set Parity Error1");
             return;
        }else{
        tcflush(fd, TCIOFLUSH);

        }
   }

    if (set_Parity(fd, datanum,stopnum, ui->jiaoyan->currentIndex()) == false) //设置校验位
       {
            QMessageBox::information(this,"termiros info","Set Parity Error2");
        return;
       }
       // r=new RTU;
        r->show();
        this->hide();





}

QString chartoQstring(char *pData,int nLength){
    char* m_pData;
    memcpy(m_pData, pData, nLength);
    int m_nLength = nLength;
    QString m_exchange;
    m_exchange.append("111");
        //char存储到QString里
        for (int i = 0; i < m_nLength; i++)
        {
            bool ok;
            QString m_tmp = QString::number(*m_pData,16);
            //接收字符为0x00，变字符串为00
            if (m_tmp.toInt(&ok,10) == 0)
            {
                m_tmp = ("00");
            }
            //接收字符为0x04,0x07等，补足0
            if ((m_tmp.toInt(&ok,10) < 10) && (m_tmp.toInt(&ok,10) > 0))
            {
                m_tmp = m_tmp.insert(0, "0");
            }

            m_exchange.append(m_tmp);
            m_exchange.append(" ");
            m_pData = m_pData + 1;
            m_tmp.clear();
        }
        return m_exchange;

}
char* Qstringtochar(char *pData,int nLength){
char *a;
return a;

}

void MainWindow::ontimeout(){
    int nread = read(fd, readbuff, sizeof (readbuff));
    printf("myread nread is %d\n", nread);
   if ((nread >= 0)) {
       qDebug()<<"Read Success!\n";
       QListWidgetItem *item=new QListWidgetItem;
       item->setText(chartoQstring(buffdata,nread));
       this->r->getshowlistwidget()->addItem(item);
   }
}

void MainWindow::mystop(){
    mytimer->setSingleShot(1);
    qDebug()<<"11111111111111111111111111111111111111111111111111111";
     this->r->getsubtut()->setEnabled(false);
}

void MainWindow::mybegin(){
    mytimer->start(1000);
    this->r->getsubtut()->setEnabled(true);
}

void  MainWindow::myDisPlay(){
     r->close();
    this->show();

    qDebug()<<"this  is  mydisplay";
}

/*
 *
thisname:%s\n
termiosname:%s\n
portrate:%d\n



 *
 *
*/

 void MainWindow::saveasfile(){

     QString filename=QFileDialog::getSaveFileName(this,"Save this",QDir::currentPath());
     qDebug()<<filename;
     if(filename.isEmpty()){
          QMessageBox::information(this,"warning","Please set a file");
          return;
     }
     this->setWindowTitle(filename);
     QFile *file=new QFile;
     file->setFileName(filename);
     bool ok=file->open(QIODevice::WriteOnly);
     if(ok){
         QString temp;
         temp.sprintf("termios name id %s parorate is %d",ui->twrmiosnameinput->text().toStdString().c_str(),ui->portrate->currentIndex()) ;
         QTextStream out(file);
         out<<temp;
          file->close();
          delete file;
          myfilename=filename;

     }else{
         QMessageBox::information(this,"Error","Failed save this ");
         return ;
     }

 }

 void MainWindow::my_open(){// 未完善
   //  int speed_arr[] = {9600,38400, 19200, 4800, 2400, 1200, 300};
     QString filename=QFileDialog::getOpenFileName(this,"Open this",QDir::currentPath());
     qDebug()<<filename;
     if(filename.isEmpty()){
          QMessageBox::information(this,"warning","Not Open File ");
          return;
     }
     QFile *file=new QFile;
     file->setFileName(filename);
     bool ok=file->open(QIODevice::ReadOnly);
     if(ok){


          QTextStream in(file);
          QString temp=in.readAll();
          char tn[20];
          //QString tn;
          int rt;
          sscanf(temp.toStdString().c_str(),"termios name id %s parorate is %d",&tn,&rt);
           ui->twrmiosnameinput->setText(tn);
           ui->portrate->setCurrentIndex(rt);
          file->close();
          delete file;
          myfilename=filename;

     }else{
         QMessageBox::information(this,"Error","Failed toOpen file \n "+file->errorString());
         return ;
     }

 }
 void MainWindow::my_exits(){
     this->close();

 }
void MainWindow::my_saves(){

    if(myfilename.isEmpty())
        MainWindow::saveasfile();
    else{
        QFile *file=new QFile;
        file->setFileName(myfilename);
        bool ok=file->open(QIODevice::WriteOnly);
        if(ok){
             QString temp;
             temp.sprintf("termios name id %s parorate is %d",ui->twrmiosnameinput->text().toStdString().c_str(),ui->portrate->currentIndex()) ;
             QTextStream out(file);
             out<<temp;
             file->close();
             delete file;


        }else{
            QMessageBox::information(this,"Error","Failed not find");
            return ;
        }

    }

}


int MainWindow::OpenDev(const char *Dev) {
    int fd = open(Dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (-1 == fd) {
        QMessageBox::information(this,"termiros info","Can't Open Serial Port!\nPlease check your port name");
        return -1;
    }
    else {
        qDebug()<<QString("success open termiros ");
        return fd;
    }
}

int MainWindow::set_Parity(int fd, int databits, int stopbits, int parity) {//端口 数据位  停止位 校验位

    struct termios options;

    if (tcgetattr(fd, &options) != 0) {
         QMessageBox::information(this,"termiros info","SetupSerial 1");
        return false;
    }
    bzero(&options, sizeof (options));
    options.c_cflag |= CLOCAL | CREAD;
    options.c_cflag &= ~CSIZE;
    switch (databits) {
        case 6:
           options.c_cflag &= ~CSIZE;
           options.c_cflag |= CS6;
           break;
        case 5:
            options.c_cflag &= ~CSIZE;
           options.c_cflag |= CS5;
           break;
        case 7:
             options.c_cflag &= ~CSIZE;
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag &= ~CSIZE;
            options.c_cflag |= CS8;
            break;
        default:
        QMessageBox::information(this,"termiros info","SetupSerial 1");
       return false;
    }
    qDebug()<<parity;
    switch (parity) {
        case 0:   /* 无校验          */
        //case 'N':
           options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            // options.c_cflag &= ~PARENB;
            break;
        case '0':
        //case 'O':
            options.c_cflag |= (PARODD | PARENB);         /* 奇校验          */
            options.c_iflag |=INPCK; //(INPCK | ISTRIP);
           // options.c_cflag |= PARENB;
            //options.c_cflag |= ~PARODD;
            break;
        case '1':
       // case 'E':
         options.c_cflag |= PARENB;
         options.c_cflag &= ~PARODD;
         options.c_iflag |= INPCK;
           // options.c_cflag |= PARENB;
          //  options.c_cflag &= ~PARODD;
          //  options.c_iflag |= (INPCK | ISTRIP);         /* 偶校验          */
            break;
    default:
        QMessageBox::information(this,"termiros info","SetupSerial2");
       return false;
    }



    switch (stopbits) {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        case 15:
            options.c_cflag &= ~CSTOPB; /* 1.5位停止位 */
        break;
    default: QMessageBox::information(this,"termiros info","SetupSeria3");
        return false;


    }

    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        QMessageBox::information(this,"termiros info","SetupSerial4");
       return false;
    }
    return 1;
}



uint16_t MainWindow::CRC(char *buff, int bufflen) {
    uint16_t CRCjicun = 0xffff;
    for (int i = 0; i < bufflen; i++) {
        CRCjicun ^= buff[i];
        for (int j = 0; j < 8; j++) {
            if (CRCjicun & 0x01)
                CRCjicun = (CRCjicun >> 1)^0xA001;
            else
                CRCjicun = CRCjicun >> 1;
        }
    }
    return CRCjicun;
}



