#ifndef MODBUSRTUCLIENT_H
#define MODBUSRTUCLIENT_H

#include <QObject>
#include <DeviceModel.h>
#include <QModbusRtuSerialSlave>
#include <QModbusRtuSerialMaster>
#include <QModbusClient>
#include <ComConfig.h>
#include <QLoggingCategory>


Q_DECLARE_LOGGING_CATEGORY(ModBusRtuClientLog)


class ModBusRtuClient : public DeviceModel
{
    Q_OBJECT
public:
    Q_PLUGIN_METADATA(IID DeviceModelPluginInterface_IID FILE "DeviceModbusRtuClient.json")
    Q_INTERFACES(DeviceModel)

    ModBusRtuClient() {};
    ~ModBusRtuClient() {};
    //开始从机模式
    void start()  Q_DECL_OVERRIDE;
    //停止
    void stop()  Q_DECL_OVERRIDE;
    //打开通讯
    void open()  Q_DECL_OVERRIDE;
    //关闭通讯端口
    void close()  Q_DECL_OVERRIDE;
    //设置 通讯通道
    void initComPort(ComPort *pPort) Q_DECL_OVERRIDE;
    //初始化 放到线程里
    bool initialize()  Q_DECL_OVERRIDE;
    //释放资源
    bool uninitialize()  Q_DECL_OVERRIDE;
    //判断设备的执行状态
    bool isRunning()  Q_DECL_OVERRIDE;
    //循环等待上位机 处理上位机的请求
    bool doLoop()  Q_DECL_OVERRIDE;
    // 初始化设备 void* pObj 指向  Dev_s QList<Dev_s> 保留了该设备模型所使用的设备  对于modbus slave 这个接口只会调用一次
     bool additionDevice(void* pObj) Q_DECL_OVERRIDE;
    // 初始化设备
    bool initailizeDevice(void* pObj)  Q_DECL_OVERRIDE;
    // 连接设备
    bool connectDevice(void* pObj)  Q_DECL_OVERRIDE;
    // 断开设备连接
    bool disconnectDevice(void* pObj)  Q_DECL_OVERRIDE;
    // 反初始化设备
    bool unInitailizeDevice(void* pObj)  Q_DECL_OVERRIDE;
    //获取发送报文
    QByteArray getSendFrame()  Q_DECL_OVERRIDE;
    //获取接收报文
    QByteArray getRevFrame()  Q_DECL_OVERRIDE;
protected slots:
    void receive_reg_data_slot(QList<reg_s*> , Dev_s*) Q_DECL_OVERRIDE;

#if 0
    //读寄存器列表
    int readRegList(RegList_s *pRegList) Q_DECL_OVERRIDE;
    //读单个寄存器
    bool readReg(Reg_Info_s info, reg_s *pReg) Q_DECL_OVERRIDE;
    //写寄存器列别
    int writeRegList(RegList_s *pRegList) Q_DECL_OVERRIDE;
    //写单个寄存器
    bool writeReg(Reg_Info_s info, reg_s *pReg) Q_DECL_OVERRIDE;
    // 写变量前处理
    bool beforeWriteReg(void* pObj, reg_s* pReg) Q_DECL_OVERRIDE;
    // 写变量后处理
    bool afterWriteReg(void* pObj, reg_s* pReg) Q_DECL_OVERRIDE;
    // 读变量前处理
    bool beforeReadReg(void* pObj, reg_s* ) Q_DECL_OVERRIDE;
    // 读变量后处理
    bool afterReadReg(void* pObj, reg_s* pReg) Q_DECL_OVERRIDE;
    //主动上报寄存器信息
    bool reportRegList(RegList_s *pRegList) Q_DECL_OVERRIDE;
    //上报单个寄存器
    bool reportReg(Reg_Info_s info, reg_s *pReg) Q_DECL_OVERRIDE;
#endif

private slots:
    void dataWrittenSlot(QModbusDataUnit::RegisterType table, int address, int size);
    void testSlot(QString slot) Q_DECL_OVERRIDE;

private:
    QModbusServer *modbusDevice = nullptr;
    Dev_s *m_Dev = nullptr;

protected:
    void setupDeviceData();
};


#endif // MODBUSRTUCLIENT_H
