#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"chwenjian.h"
#include"mytermios.h"
#include"rtu.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void Qstringtochar(QString &temp,int len);
    int CRC();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString myfilename;
    RTU *r;
    char buffdata[1024],readbuff[1024];
    int bufflen;
     QTimer *mytimer;
     int fd;
private slots:
    void on_pushButton_4_clicked();
    void saveasfile();
    void my_open();
    void my_exits();
    void my_saves();
    void myDisPlay();
    void ontimeout();
    void mystop();
    void mybegin();
    void mysubmit();

private:
    Ui::MainWindow *ui;
  //  RTU *rtu=new RTU;
    int set_Parity(int fd, int databits, int stopbits, int parity);

    int OpenDev(const char *Dev);
 //   void getTermiosdata(int fd);
    void mysend(QString te);


};

#endif // MAINWINDOW_H
