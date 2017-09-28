#ifndef THIRED_H
#define THIRED_H

#include <QWidget>
#include<chwenjian.h>
namespace Ui {
class thired;
}

class thired : public QWidget
{
    Q_OBJECT

public:
    explicit thired(QWidget *parent = 0);
    ~thired();
    Ui::thired *ui;
    QRadioButton* getread();
    QRadioButton* getwrite();
    QPushButton* subbut();
    QLineEdit* getjicunvalue();
    QRadioButton* getradioread();
    QLineEdit* getmachineaddress();
    QLineEdit* getaddress();
    QLineEdit* getaddresslenth();
    QPushButton* getsubmit();

private slots:
    void on_exitbut_2_clicked();
      void  changeMyValue();
};

#endif // THIRED_H
