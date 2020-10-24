#include <QCoreApplication>
#include <QThread>
#include <PluginManager.h>
#include <DeviceModel.h>
#include <ComPort.h>
#include "ComConfig.h"


#define PORT_LIB "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/ComPortLibrary/ComPortLibrary/SerialPortLibrary/debug"
int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);

    #if 1
    QString path = "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/DeviceLibrary/DeviceLibrary/DeviceModbusRtuClient/debug";
    DeviceModel *pDeviceModel = (qobject_cast<DeviceModel *>)(PluginManager::getInstance()->loadPluginPath(path, "DeviceModbusRtuClient"));

    ComPort *port = (qobject_cast<ComPort *>)(PluginManager::getInstance()->loadPluginPath(PORT_LIB, "SerialPortLibrary"));
    ComConfig::ReadXml("I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml");

    QList<Dev_s*> &pList =  ComConfig::GetVirDevList();

    const Dev_s *pDev = nullptr;

    for(int i=0; i<pList.length(); i++)
    {
        if(pList.at(i)->DeviceLibrary == "DeviceModbusRtuClient")
        {
            pDev = pList.at(i);
        }
    }

    if(port)
    {
        qDebug()<<"SerialPortLibrary dll open ok";
        if(pDeviceModel)
        {
            qDebug()<<"DeviceModbusRtuClient dll open ok";
            pDeviceModel->initialize();
            pDeviceModel->start();
            pDeviceModel->initComPort(port);
            pDeviceModel->additionDevice((void*)pDev);
            bool res = pDeviceModel->initailizeDevice(nullptr);
            if(!res)
            {
                qDebug()<<"pDeviceModel initailizeDevice error";
            }
//            while (1) {
//                pDeviceModel->doLoop();
////                QThread::sleep(1);
//            }
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

#endif

    return a.exec();
}
