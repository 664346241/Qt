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

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString myfilename;
    RTU *r;
    char buffdata[1024],readbuff[1024];
    int bufflen;
     QTimer *mytimer;
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

private:
    Ui::MainWindow *ui;
  //  RTU *rtu=new RTU;
    int set_Parity(int fd, int databits, int stopbits, int parity);
    uint16_t CRC(char *buff, int bufflen);
    int OpenDev(const char *Dev);
    void getTermiosdata(int fd);


};

#endif // MAINWINDOW_H
