#ifndef MYTERMIOS_H
#define MYTERMIOS_H
#include"chwenjian.h"

class MyTermios
{
public:
    QString name;
    bool qioujiaoyan;
    int datanum;
    int portrate;
    int stopnum;
    MyTermios(QString name,int qioujiaoyan,int datanum,int portrate,int stopnum );
    MyTermios();
};

#endif // MYTERMIOS_H
