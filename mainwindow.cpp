#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace MainWindow

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("termiros setting");
    QObject::connect(ui->actionSave_S,SIGNAL(triggered()),this,SLOT(saveasfile()) );
    QObject::connect(ui->actionExit_q,SIGNAL(triggered()),this,SLOT(my_exits()) );
    QObject::connect(ui->actionOpen_O,SIGNAL(triggered()),this,SLOT(my_open()) );
    QObject::connect(ui->actionSaves,SIGNAL(triggered()),this,SLOT(my_saves()) );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    int speed_arr[] = {9600,38400, 19200, 4800, 2400, 1200, 300};
    QString MyTermiosName=ui->twrmiosnameinput->text();
    int PortRate=speed_arr[ui->portrate->currentIndex()];
    int datanum=ui->datanum->currentText().toInt();

    QString res;
    QString  tt;
    tt.sprintf("\n Port Rate is%d \n DataNum is %d",PortRate,datanum);
    res.append("termiros  Name is ：").append(MyTermiosName).append(tt);
    QMessageBox::information(this,"termiros info",res);
    //accept();

    int stopnum=0;
    if(this->ui->radiostop1->isChecked()){
        stopnum=1;

    }
    //if(this->ui->radiostop15->isChecked()){
   //     stopnum=15;

  //  }
    if(this->ui->radiostop2->isChecked()){
        stopnum=2;

    }
    qDebug()<<stopnum;
//   MyTermios *myt=new MyTermios(MyTermiosName,ui->radioButton->isChecked(),datanum,PortRate,ui->jiaoyan->currentIndex());
    bufflen=0;
    int fd;

    fd = OpenDev(MyTermiosName.toStdString().c_str()); //打开串口
    if (fd > 0) {
        set_speed(fd, speed_arr[PortRate]); //设置波特率
        printf("Open Serial Port %s\n", dev_name);
    } else {

        return ;
    }
    if (set_Parity(fd, datanum,stopnum, ui->jiaoyan->currentIndex()) == WD_FALSE) //设置校验位
       {
           QMessageBox::information(this,"termiros info","Set Parity Error");
        return;
       }
    r=new RTU;
    r->myTermios=myt;
    r->show();
    this->hide();
    connect(this->r->getactionret(),SIGNAL(triggered()),this,SLOT(myDisPlay()));
 /*   QThread t;
       QTimer timer;
       Worker worker;

       QObject::connect(&timer, SIGNAL(timeout()), &worker, SLOT(onTimeout()));
       timer.start(1000);

       worker.moveToThread(&t);

       t.start();

    */




}

void MainWindow::getTermiosdata(){
    int nread;
    nread = read(fd,buffdata, sizeof (rebuff));
    printf("read nread is %d\n", nread);
    if ((nread > 0)) {
        printf("Read Success!\n");
       // this->r->
        //需要添加到RTU中去
    }

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


int MainWindow::OpenDev(char *Dev) {
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
           opt->c_cflag |= CS6;
           break;
        case 5:
           opt->c_cflag |= CS5;
           break;
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
        QMessageBox::information(this,"termiros info","SetupSerial 1");
       return false;
    }
    switch (parity) {
        case 0:   /* 无校验          */
        //case 'N':
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
        case '0':
        //case 'O':
            options.c_cflag |= (PARODD | PARENB);         /* 奇校验          */
            options.c_iflag |= (INPCK | ISTRIP);
            break;
        case '1':
       // case 'E':
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            options.c_iflag |= (INPCK | ISTRIP);         /* 偶校验          */
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
        for (j = 0; j < 8; j++) {
            if (CRCjicun & 0x01)
                CRCjicun = (CRCjicun >> 1)^0xA001;
            else
                CRCjicun = CRCjicun >> 1;
        }
    }
    return CRCjicun;
}



