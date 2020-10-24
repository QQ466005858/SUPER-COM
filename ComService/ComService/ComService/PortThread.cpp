#include "PortThread.h"
//#include <RealTimeDB.h>
#include <QDebug>


PortThread::PortThread(QString name)
{
    m_name = name;
    mbIsRunning = false;
}

PortThread::~PortThread()
{

}

void PortThread::AddVendor(DevMd_t &p)
{
    m_DevMdList.append(p);
}

/*
* 是否运行
*/
bool PortThread::IsRunning()
{
    return mbIsRunning;
}


/*
* 启动
*/
void PortThread::Start()
{
    if(mbIsRunning)
        return;
    mbIsRunning = true;
//    foreach (DevMd_t Vendor, m_DevMdList) {
//        if(Vendor.model != Q_NULLPTR) {
//            if(!Vendor.model->isRunning()) {
//                Vendor.model->start();
//            }
//        }
//    }
    this->start();
}


/*
* 停止
*/
void PortThread::Stop()
{
    mbIsRunning = false;
    foreach (DevMd_t Vendor, m_DevMdList) {
        if(Vendor.model != Q_NULLPTR) {
            if(Vendor.model->isRunning()) {
                Vendor.model->stop();
                Vendor.model->close();
            }
        }
    }
    this->wait();
}


void PortThread::run()
{
    qDebug()<< "PortThread run:" << m_name;
    foreach (DevMd_t Vendor, m_DevMdList) {
        if(Vendor.model != Q_NULLPTR) {
            if(!Vendor.model->isRunning()) {
                Vendor.model->open();
                //TODO:在这里可以初始化通道然后给设备传递过去 如果 设备需要这个通道就使用即可，不需要那就 关闭 通道 释放资源
                ComPort *pComPort = nullptr;
                Vendor.model->initComPort(nullptr);
//                QString com = Vendor.dev->port.split(',').first();
//                Vendor.model->initailizeDevice((void*)Vendor.dev_list);//给设备模型指定设备数据
                foreach(Dev_s *dev, Vendor.dev_list)
                {
                    Vendor.model->initailizeDevice(dev);//增加设备 需要维护一个设备列表
                }
                Vendor.model->start();
            }
        }
    }
    while(mbIsRunning) {
//        /RealTimeDB::instance()->addNeedWriteTagToDeviceWriteQueue();
        foreach (DevMd_t Vendor, m_DevMdList) {
            if(!mbIsRunning)
                return;
            if(Vendor.model != Q_NULLPTR) {
                Vendor.model->doLoop();//处理设备事务
            }
        }
        this->msleep(5);
    }
    exec();
}

