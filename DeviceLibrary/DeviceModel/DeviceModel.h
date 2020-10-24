#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>

class ComPort;
struct reg_s;
struct reg_dev_s;
struct Dev_s;


class ComConfig;
//设备模型的基类
class DeviceModel :public QObject
{
    Q_OBJECT
public:
    virtual ~DeviceModel() {};
    //纯虚函数
    //开始从机模式
    virtual void start() = 0;
    //停止
    virtual void stop() = 0;
    //打开通讯
    virtual void open() = 0;
    //关闭通讯端口
    virtual void close() = 0;
    //设置 通讯通道
    virtual void initComPort(ComPort *pPort) = 0;
    //初始化 放到线程里
    virtual bool initialize() = 0;
    //释放资源
    virtual bool uninitialize() = 0;
    //判断设备的执行状态
    virtual bool isRunning() = 0;
    //循环等待上位机 处理上位机的请求
    virtual bool doLoop() = 0;
    // 初始化设备 void* pObj 指向  Dev_s QList<Dev_s> 保留了该设备模型所使用的设备
    virtual bool additionDevice(void* pObj) = 0;
    //获取发送报文
    virtual QByteArray getSendFrame() = 0;
    //获取接收报文
    virtual QByteArray getRevFrame() = 0;
    //初始化设备
    virtual bool initailizeDevice(void* pObj) = 0;
    // 连接设备
    virtual bool connectDevice(void* pObj) = 0;
    // 断开设备连接
    virtual bool disconnectDevice(void* pObj) = 0;
    // 反初始化设备
    virtual bool unInitailizeDevice(void* pObj) = 0;

#if 0
    //读寄存器列表
    virtual int readRegList(RegList_s *pRegList) {}
    //读单个寄存器
    virtual bool readReg(Reg_Info_s info, reg_s *pReg) {}
    //写寄存器列别
    virtual int writeRegList(RegList_s *pRegList) {}
    //写单个寄存器
    virtual bool writeReg(Reg_Info_s info, reg_s *pReg) {}
    // 写变量前处理
    virtual bool beforeWriteReg(void* pObj, reg_s* pReg) {}
    // 写变量后处理
    virtual bool afterWriteReg(void* pObj, reg_s* pReg) {}
    // 读变量前处理
    virtual bool beforeReadReg(void* pObj, reg_s* ) {}
    // 读变量后处理
    virtual bool afterReadReg(void* pObj, reg_s* pReg) {}
    //主动上报寄存器信息
    virtual bool reportRegList(RegList_s *pRegList) {}
    //上报单个寄存器
    virtual bool reportReg(Reg_Info_s info, reg_s *pReg) {}
#endif

signals:
    void report_reg_data_signal( QList<reg_s*>, Dev_s *);
    void testSignal(QString);
public slots:
    virtual void receive_reg_data_slot(QList<reg_s*>, Dev_s *) = 0;
    virtual void testSlot(QString slot) = 0;
signals:
    void report_reg_write_signal( QList<reg_s*>, Dev_s *);

};




QT_BEGIN_NAMESPACE

#define DeviceModelPluginInterface_IID "DeviceLibrary.DeviceLibrary.DeviceModel"

Q_DECLARE_INTERFACE(DeviceModel, DeviceModelPluginInterface_IID);// Q_DECLARE_INTERFACE(接口类名, 接口标识符)

QT_END_NAMESPACE

#endif // DEVICEMODEL_H
