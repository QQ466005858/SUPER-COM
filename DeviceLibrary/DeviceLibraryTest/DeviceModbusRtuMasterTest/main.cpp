#include <QCoreApplication>
#include <QCoreApplication>
#include <QThread>
#include <PluginManager.h>
#include <DeviceModel.h>
#include <ComPort.h>
#include "ComConfig.h"

#include "DevModelThread.h"



#define PORT_LIB "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/ComPortLibrary/ComPortLibrary/SerialPortLibrary/debug"
#define DEV_MODEL  "DeviceModbusRtuMaster"

#include <QTimer>


#include <QObject>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/DeviceLibrary/DeviceLibrary/DeviceModbusRtuMaster/debug";
    DeviceModel *pDeviceModel = (qobject_cast<DeviceModel *>)(PluginManager::getInstance()->loadPluginPath(path, DEV_MODEL));

    ComPort *port = (qobject_cast<ComPort *>)(PluginManager::getInstance()->loadPluginPath(PORT_LIB, "SerialPortLibrary"));
    ComConfig::ReadXml("I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml");

    QList<Dev_s*> &pList =  ComConfig::GetPhyDevList();

    QList<Dev_s*>  MbDevList;

     qDebug()<<"GetPhyDevList: len :"<<pList.length();


    for(int i=0; i<pList.length(); i++)
    {
        qDebug()<<"DeviceLibrary:"<<pList.at(i)->DeviceLibrary<<i;

        if(pList.at(i)->DeviceLibrary == DEV_MODEL)
        {
            qDebug()<<"find DeviceModbusRtuMaster";
            MbDevList.append(  pList.at(i));
            break;
        }
        else
        {
            qDebug()<<" DeviceModbusRtuMaster:"<<pList.at(i)->DeviceLibrary;
        }
    }
    if(!MbDevList.length())
    {
        qDebug()<<"###############find DeviceModbusRtuMaster ERROR ##############";
        exit(-1);
    }

    if(port)
    {
        qDebug()<<"SerialPortLibrary dll open ok";
        if(pDeviceModel)
        {
            qDebug()<<DEV_MODEL<<"dll open ok";
            DevModelThread *pThread = new DevModelThread(pDeviceModel, MbDevList, MbDevList.first());
            pThread->start();
        }
        else
        {
            qDebug()<<"DeviceModel dll open error";
        }
    }
    else
    {
        qDebug()<<"ComPort dll open error";
    }
    qDebug()<<"test finshed";
    return a.exec();
}
