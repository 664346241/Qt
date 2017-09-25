#ifndef SENDANDWRITE_H
#define SENDANDWRITE_H

#include <QDialog>
#include<chwenjian.h>

namespace Ui {
class Sendandwrite;
}

class Sendandwrite : public QDialog
{
    Q_OBJECT

public:
    explicit Sendandwrite(QWidget *parent = 0);
    ~Sendandwrite();
    Ui::Sendandwrite *ui;

private:

};

#endif // SENDANDWRITE_H
