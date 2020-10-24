#ifndef MODBUSRTUSERVER_H
#define MODBUSRTUSERVER_H

#include <DeviceModel.h>
#include <QModbusClient>

#include <QLoggingCategory>
#include <modbus.h>


#define LIBMODBUS

struct Dev_s;

Q_DECLARE_LOGGING_CATEGORY(ModBusRtuMasterLog)

class ModbusRtuMaster : public DeviceModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeviceModelPluginInterface_IID FILE "DeviceModbusRtuMaster.json")
    Q_INTERFACES(DeviceModel)
public:

    ModbusRtuMaster() {};
    ~ModbusRtuMaster() {};
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
    //设备寄存器数据改变槽
    void receive_reg_data_slot( QList<reg_s *>, Dev_s *) Q_DECL_OVERRIDE;

private slots:
    void read_reg_finished_slot();
    void write_reg_finished_slot();

public slots:
    void testSlot(QString slot) Q_DECL_OVERRIDE;

private:
    QList<Dev_s*> m_SlaveDevList;
    QHash <int, Dev_s*>m_SlaveHash;//KEY:ADDR
    QHash <int , reg_s*>m_HoldRegHash;//保持寄存器 hash 表
    QHash <int , reg_s*>m_InputRegHash;//输入寄存器hash 表


    Dev_s *m_Dev = nullptr;//保存主站信息

#ifndef LIBMODBUS
    QModbusClient *modbusDevice = nullptr;
#else
    modbus_t *ctx = nullptr;
#endif

private:
#ifndef LIBMODBUS
    QModbusReply * readHoldReg(int serverAddress, int reg_start, int num);
    QModbusReply * writeHoldReg(int serverAddress, int reg_star, QVector<quint16> &Values);
    QModbusReply * readInputReg(int serverAddress, int reg_start, int num);
#endif

//    QModbusReply *reply;
};

#endif // MODBUSRTUSERVER_H
