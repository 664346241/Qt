#ifndef RTU_H
#define RTU_H
#include"chwenjian.h"
#include"thired.h"
#include"mytermios.h"
namespace Ui {
class RTU;
}

class RTU : public QMainWindow
{
    Q_OBJECT

public:
    explicit RTU(QWidget *parent = 0);
    ~RTU();
     Ui::RTU *ui;
     MyTermios *myTermios;
     thired *mydialog;
     QAction* getactionret();
     QTextEdit* getinputlineedit();
     QPushButton* getsubtut();
     QPushButton* getendbut();
     QPushButton* getbegbut();
     QListWidget* getshowlistwidget();
     QListWidget* gethistoryWidget();
private slots:
    void on_pushButton_clicked();
    void my_exit();
  //  void my_ret();
    void my_temp();
    void my_date();
    void my_setFont();
    void my_read();
    void my_write();

protected:
    bool eventFilter(QObject *obj, QEvent *e);
private:
    int my_xieyi;

};

#endif // RTU_H
