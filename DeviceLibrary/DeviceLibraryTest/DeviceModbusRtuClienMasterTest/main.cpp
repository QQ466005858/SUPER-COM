#include <QCoreApplication>
#include <QCoreApplication>
#include <QThread>
#include <PluginManager.h>
#include <DeviceModel.h>
#include <ComPort.h>
#include "ComConfig.h"
#include "DevModelThread.h"
#include <QMetaType>
#include "ComShareMemory.h"


#define PORT_LIB "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/ComPortLibrary/ComPortLibrary/SerialPortLibrary/debug"
#define DEV_MODEL_MASTER  "DeviceModbusRtuMaster"
#define DEV_MODEL_CLIENT  "DeviceModbusRtuClient"
#define CONFIG_FILE_PATH  "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml"
QString client_path = "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/DeviceLibrary/DeviceLibrary/DeviceModbusRtuClient/debug";
QString server_path = "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM-Debug/DeviceLibrary/DeviceLibrary/DeviceModbusRtuMaster/debug";

DeviceModel *pSlave = nullptr;
DeviceModel *pMaster = nullptr;


ComConfig * ComRes =ComConfig::instance();


int client_init()
{
    pSlave = (qobject_cast<DeviceModel *>)(PluginManager::getInstance()->loadPluginPath(client_path, DEV_MODEL_CLIENT));
    ComPort *port = (qobject_cast<ComPort *>)(PluginManager::getInstance()->loadPluginPath(PORT_LIB, "SerialPortLibrary"));
    QList<Dev_s*> &pList =  ComRes->GetVirDevList();
     Dev_s *pDev = nullptr;
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
        if(pSlave)
        {
            qDebug()<<"DeviceModbusRtuClient dll open ok";

            //    DevModelThread(DeviceModel *p,  QList<Dev_s*> DevL, Dev_s * mb);
            DevModelThread *pThread = new DevModelThread(pSlave, pList, pDev, ComRes);
            pThread->start();
//            pSlave->initialize();
//            pSlave->start();
//            pSlave->initComPort(port);
//            pSlave->additionDevice((void*)pDev);
//            bool res = pSlave->initailizeDevice(nullptr);
//            if(!res)
//            {
//                qDebug()<<"pSlave initailizeDevice error";
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
    return  0;
}

int master_init()
{
    pMaster = (qobject_cast<DeviceModel *>)(PluginManager::getInstance()->loadPluginPath(server_path, DEV_MODEL_MASTER));
    ComPort *port = (qobject_cast<ComPort *>)(PluginManager::getInstance()->loadPluginPath(PORT_LIB, "SerialPortLibrary"));
    QList<Dev_s*> &pList =  ComRes->GetPhyDevList();
    QList<Dev_s*>  MbDevList;
    qDebug()<<"GetPhyDevList: len :"<<pList.length();
    for(int i=0; i<pList.length(); i++)
    {
        qDebug()<<"DeviceLibrary:"<<pList.at(i)->DeviceLibrary<<i;

        if(pList.at(i)->DeviceLibrary == DEV_MODEL_MASTER)
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
        if(pMaster)
        {
            qDebug()<<DEV_MODEL_MASTER<<"dll open ok";
            QObject::connect(pMaster, &DeviceModel::report_reg_data_signal, pSlave, &DeviceModel::receive_reg_data_slot);
            QObject::connect(pMaster, &DeviceModel::testSignal, pSlave, &DeviceModel::testSlot);
            DevModelThread *pThread = new DevModelThread(pMaster, MbDevList, MbDevList.first(), ComRes);
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

}
//    void report_reg_data_signal( QList<reg_s *> reg_info, Dev_s *dev);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ComRes->ReadXml(CONFIG_FILE_PATH);
    ComRes->test_dump();
    int mem_size = ComRes->get_reg_num() * sizeof(reg_s);
    qDebug()<<"mem_size:"<<mem_size<<"get_reg_num:"<<ComRes->get_reg_num();
    bool res = ComShareMemory::instance()->init_share_memory(ComRes->get_all_reg_list());
    if(res)
    {
        qDebug()<<"共享内存创建成功:"<<res;
    }
    else
    {
        qDebug()<<"共享内存创建失败:"<<res;
    }
    qDebug()<<"ComConfig addr:"<<(uint32_t)&ComRes;
    qRegisterMetaType<reg_s>("reg_s");//注册MeterAdjStep类型
    qRegisterMetaType<reg_s*>("reg_s*");//注册MeterAdjStep类型
    qRegisterMetaType<QList<reg_s*>>("QList<reg_s *>");//注册MeterAdjStep类型
    qRegisterMetaType<Dev_s*>("Dev_s*");//注册MeterAdjStep类型
    qRegisterMetaType<Dev_s>("Dev_s");//注册MeterAdjStep类型
    qRegisterMetaType<QList<reg_s>>("QList<reg_s>");//注册MeterAdjStep类型
    client_init();
    master_init();
    qDebug()<<"test finshed";
    return a.exec();
}
