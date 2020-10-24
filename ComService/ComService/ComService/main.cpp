#include <QCoreApplication>
#include "ComService.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    ComService mComService;

    mComService.Load("I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml");

    qDebug()<<__func__<<"mComService:Load-"<<"end";

    return a.exec();
}
