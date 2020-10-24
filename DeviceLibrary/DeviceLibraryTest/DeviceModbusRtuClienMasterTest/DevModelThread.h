#ifndef DEVMODELTHREAD_H
#define DEVMODELTHREAD_H

#include <QObject>
#include <QtDebug>

#include <QThread>
#include <DeviceModel.h>

class TestClass : public QObject
{
    Q_OBJECT
public:
    TestClass();
    ~TestClass();
signals:
    void testSignal(QString msg);
public slots:
    void testSlot(QString slot)
    {
        qDebug()<<__func__<<slot<<"##########################";
    }
};


class DevModelThread : public QThread
{
    Q_OBJECT
public:
    DevModelThread(DeviceModel *p,  QList<Dev_s*> DevL, Dev_s * mb,  ComConfig *cfg);
    ~DevModelThread(){}
protected:
    DeviceModel *m_DeviceModel = nullptr;
    QList<Dev_s*> Dev_list;
    Dev_s * m_ModeDev = nullptr;
     ComConfig *m_com = nullptr;
private:
    int loop_cnt = 1000;
protected:
    void run() override
    {
        m_DeviceModel->initialize();
        foreach(Dev_s *dev, Dev_list)
        {
            m_DeviceModel->additionDevice((void*)dev);
        }
        bool res = m_DeviceModel->initailizeDevice(m_ModeDev);
//        m_DeviceModel->connectDevice(NULL);
        if(!res)
        {
            qDebug()<<"pDeviceModel initailizeDevice error";
            quit();
        }
        while (--loop_cnt)
        {
            m_DeviceModel->doLoop();
            msleep(1000);
//            emit testSignal("run 测试信号");
        }
    }
signals:
    void testSignal(QString msg);
public slots:
    void testSlot(QString slot)
    {
        qDebug()<<__func__<<slot<<"##########################";
    }
};


#endif // DEVMODELTHREAD_H
