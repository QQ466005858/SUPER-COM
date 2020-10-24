#ifndef PORTTHREAD_H
#define PORTTHREAD_H

#include <QObject>
#include <QQueue>
#include <QList>
#include <QThread>
#include <QSemaphore>
//#include "Vendor.h"
#include <DeviceModel.h>

#include <ComConfig.h>

typedef struct device_module_dev_s
{
    DeviceModel * model = nullptr;
    QList<Dev_s *> dev_list;//设备列表
}DevMd_t;

class PortThread : public QThread
{
    Q_OBJECT
public:
    PortThread(QString name);
    ~PortThread();
    void AddVendor(DevMd_t &p);
    // 是否运行
    bool IsRunning();
    // 启动
    void Start();
    // 停止
    void Stop();

protected:
    void run();

private:
    bool mbIsRunning;
    QList<DevMd_t> m_DevMdList;
//    QList<Dev_s *>m_DevPort;//保留了该端口要带的设备指针
    QString m_name;
};

#endif // PORTTHREAD_H
