#ifndef MYDIOLOG_H
#define MYDIOLOG_H

#include"chwenjian.h"

namespace Ui {
class Mydiolog;
}

class Ui::Mydiolog : public QWidget
{
    Q_OBJECT

public:
     Ui:: Mydiolog *ui;
    explicit Mydiolog(QWidget *parent = 0);
    ~Mydiolog();


private slots:
   //  void on_subbut_clicked();

    // void on_radioButton_3_clicked();

};

#endif // MYDIOLOG_H
