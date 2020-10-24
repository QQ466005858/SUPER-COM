#include "ModbusRtuMaster.h"
#include <DeviceModel.h>
#include <QModbusRtuSerialSlave>
#include <QModbusRtuSerialMaster>
#include <QModbusClient>
#include <ComConfig.h>
#include "ComShareMemory.h"


Q_LOGGING_CATEGORY(ModBusRtuMasterLog, "DeviceLibrary.ModbusRtuMaster.log")


//开始从机模式
void ModbusRtuMaster::start(){
    qCDebug(ModBusRtuMasterLog())<<__func__;
}

//停止
void ModbusRtuMaster::stop(){
    qCDebug(ModBusRtuMasterLog())<<__func__;
}

//打开通讯
void ModbusRtuMaster::open(){
    qCDebug(ModBusRtuMasterLog())<<__func__;
}

//关闭通讯端口
void ModbusRtuMaster::close(){
    qCDebug(ModBusRtuMasterLog())<<__func__;
}

//初始化 放到线程里
bool ModbusRtuMaster::initialize(){

    qCDebug(ModBusRtuMasterLog())<<__func__;
#ifndef LIBMODBUS


    modbusDevice = new QModbusRtuSerialMaster();
#else
//    ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
//    modbus_set_slave(ctx, SERVER_ID);
#endif

    //信号与槽测试
//    connect(this, &ModbusRtuMaster::test_signal, this, &ModbusRtuMaster::test_slot);
    return true;
}

//释放资源
bool ModbusRtuMaster::uninitialize(){

    qCDebug(ModBusRtuMasterLog())<<__func__;
    return true;
}

//判断设备的执行状态
bool ModbusRtuMaster::isRunning(){
    qCDebug(ModBusRtuMasterLog())<<__func__;
    return true;
}

#ifndef LIBMODBUS

QModbusReply * ModbusRtuMaster::readHoldReg(int serverAddress, int reg_start, int num)
{
    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qCWarning(ModBusRtuMasterLog())<<__func__<<"Need Reconnect";
        modbusDevice->connectDevice();
    }
    static QModbusDataUnit data(QModbusDataUnit::HoldingRegisters, reg_start, num);
    return modbusDevice->sendReadRequest(data, serverAddress);
}

QModbusReply * ModbusRtuMaster::writeHoldReg(int serverAddress, int reg_star, QVector<quint16> &Values)
{
    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->connectDevice();
    }
    static QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, reg_star, Values);
    return modbusDevice->sendWriteRequest(writeUnit, serverAddress);
}

QModbusReply * ModbusRtuMaster::readInputReg(int serverAddress, int reg_start, int num)
{
    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->connectDevice();
    }
    static QModbusDataUnit data(QModbusDataUnit::InputRegisters, reg_start, num);
    return modbusDevice->sendReadRequest(data, serverAddress);
}

#endif



//写寄存器完成槽函数
void ModbusRtuMaster::write_reg_finished_slot()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
    return;

    Dev_s * dev = m_SlaveHash[reply->serverAddress()];
//    if (reply->error() == QModbusDevice::NoError)
//    {
        const QModbusDataUnit unit = reply->result();
        int start_addr = unit.startAddress();
        QHash <int , reg_s*> *pRegHash = nullptr;
        //如果是保持寄存器
        if(unit.registerType() == QModbusDataUnit::HoldingRegisters)
        {
            pRegHash = &m_HoldRegHash;
        }
        else if(unit.registerType() == QModbusDataUnit::InputRegisters)
        {
            pRegHash = &m_InputRegHash;
        }
        if(pRegHash)
        {
            QList<reg_s *> reg_list;
            reg_list.clear();
            for (uint i = 0; i < unit.valueCount(); i++)
            {
                int reg_addr = start_addr + i;
                reg_s * reg = pRegHash->value(reg_addr);
                if (reply->error() == QModbusDevice::NoError)
                    reg->b_reg_write = true;
                if(reg)
                {
                    //上报数据信号
                    reg_list.append(reg);
                }
            }
            //发送写寄存器成功信号
            emit report_reg_write_signal(reg_list, dev);
        }
//    }
//    else if (reply->error() == QModbusDevice::ProtocolError)
//    {
//    }
//    else if (reply->error() != QModbusDevice::NoError)
//    {
//    }

    reply->deleteLater();
}

//读寄存器完成槽函数
void ModbusRtuMaster::read_reg_finished_slot()
{
    qCDebug(ModBusRtuMasterLog())<<__func__;

    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
    {
        qCDebug(ModBusRtuMasterLog())<<__func__<<"#ERROR#";
        return;
    }
#if 0

    int serverAddress = reply->serverAddress();
    //获取设备地址
    Dev_s * slave_dev = m_SlaveHash[serverAddress];
    if(!slave_dev)
        return;
    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        int start_addr = unit.startAddress();

        QHash <int , reg_s*> *pRegHash = nullptr;
        //如果是保持寄存器
        if(unit.registerType() == QModbusDataUnit::HoldingRegisters)
        {
            pRegHash = &m_HoldRegHash;
        }
        else if(unit.registerType() == QModbusDataUnit::InputRegisters)
        {
            pRegHash = &m_InputRegHash;
        }
        if(pRegHash)
        {
            QList<reg_s *> reg_list;
            reg_list.clear();
            for (uint i = 0; i < unit.valueCount(); i++)
            {
                int reg_addr = start_addr + i;
                QVariant reg_val = unit.value(i);
                reg_s * reg = pRegHash->value(reg_addr);
                if(reg)
                {
                    reg->reg_val = reg_val;
                    //上报数据信号
                    reg_list.append(reg);
                }
            }
            emit report_reg_data_signal(reg_list, slave_dev);
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {

    }
    else
    {

    }

#endif

    reply->deleteLater();
}


void ModbusRtuMaster::testSlot(QString slot)
{
    qCDebug(ModBusRtuMasterLog())<<__func__<<"slot:"<<slot;
}

//void ModbusRtuMaster::test_slot(QString slot)
//{
//    qCDebug(ModBusRtuMasterLog())<<__func__<<"slot:"<<slot;
//}


//循环等待上位机 处理上位机的请求
bool ModbusRtuMaster::doLoop()
{


    static int cnt = 0;
    reg_s tmp_reg;
    tmp_reg.id = QString::number(cnt);
    tmp_reg = ComShareMemory::instance()->get_reg_by_index(0);
    qCDebug(ModBusRtuMasterLog())<<__func__<<"tmp_reg.id:"<<tmp_reg.id;

    foreach(Dev_s * dev, m_SlaveDevList)
    {
        int addr = dev->addr;
        qCDebug(ModBusRtuMasterLog())<<__func__<<"addr:"<<addr;

        foreach(RegList_s read_reg, dev->ReadRegList)
        {
#if 0
            if(read_reg.reg_info.type == "HoldReg")
            {
                int reg_start = read_reg.reg_info.reg_start;
                int reg_num = read_reg.reg_info.reg_num;

                qCDebug(ModBusRtuMasterLog())<<__func__<<"reg_start:"<<reg_start<<"reg_num:"<<reg_num;

#ifndef LIBMODBUS

                if (  auto reply = readHoldReg(addr, reg_start, reg_num) )
                {
                    if (!reply->isFinished())
                    {
                        qCDebug(ModBusRtuMasterLog())<<__func__<<" connect finished & read_reg_finished_slot";
//                        connect(reply, &QModbusReply::finished, this, &ModbusRtuMaster::read_reg_finished_slot,  Qt::DirectConnection);
                        connect(reply, &QModbusReply::finished, this, &ModbusRtuMaster::read_reg_finished_slot);
//                        emit reply->finished();
                    }
                    else
                    {
                        delete reply; // broadcast replies return immediately
                        qCDebug(ModBusRtuMasterLog())<<__func__<<" broadcast replies return immediately";
                    }
                }
                else
                {
                    qCDebug(ModBusRtuMasterLog())<<__func__<<"readHoldReg:"<<"#ERROR#";
                }
#else
                //设置地址
                modbus_set_slave(ctx, addr);
                modbus_set_response_timeout(ctx, 0, dev->res_time * 1000);
                QVector<uint16_t>reg_var;
                reg_var.resize(reg_num);
                int reg_num_r = modbus_read_registers(ctx, reg_start, reg_num, reg_var.data());
                if(reg_num_r > 0)
                {
                    QString signal = read_reg.reg_info.type + "read reg num :" + QString::number(reg_num_r);
                    for(int i=0; i<reg_num_r; i++)
                    {
                        reg_s * reg = read_reg.reg_list.at(i);
                        reg->reg_val = reg_var.at(i);
                    }
//                    Dev_s * slave_dev = m_SlaveHash[addr];
                    //上报设备寄存数据
                    qCDebug(ModBusRtuMasterLog())<<__func__<<"readHoldReg:上报数据";
//                    emit testSignal("MODBUS MASTER 测试信号");
                    emit report_reg_data_signal( read_reg.reg_list, dev);
                }
                else
                {
                    qCDebug(ModBusRtuMasterLog())<<__func__<<"寄存器读取错误";
                    //读取错误
                }
#endif
            }
#endif

        }

    }
    return true;
}



//接收到设备更改的信号与槽
void ModbusRtuMaster::receive_reg_data_slot(QList<reg_s *> reg_info_l, Dev_s * dev)
{

    qCDebug(ModBusRtuMasterLog())<<__func__;

    //如果当前协议栈有这个设备
    if(m_SlaveDevList.indexOf(dev) != -1)
    {
        int dev_addr = dev->addr;
        int reg_start = reg_info_l.first()->reg_addr;
        QVector<quint16> reg_write;

        foreach(reg_s * reg_info, reg_info_l)
        {
            quint16 reg_val = reg_info->rev_write_val.toInt();
            reg_info->b_reg_write = false;
            reg_write.append(reg_val);
        }
        modbus_set_slave(ctx, dev_addr);
        int wirte_res = modbus_write_registers(ctx, reg_start, reg_write.length(), reg_write.data());
        if(wirte_res >0)
        {
            //写入成功
        }
//        if (auto *reply = this->writeHoldReg(dev_addr, reg_start, reg_write) ) {
//            if (!reply->isFinished()) {
//                connect(reply, &QModbusReply::finished, this, &ModbusRtuMaster::write_reg_finished_slot);
//            } else {
//                // broadcast replies return immediately
//                reply->deleteLater();
//            }
//        } else {

//        }

    }
}
#ifndef LIBMODBUS

#endif




//增加设备 pObj 指向 Dev_s 指针结构体
bool ModbusRtuMaster::additionDevice(void* pObj){

    Dev_s *Dev = (Dev_s*)(pObj);
    if(!pObj)
        return false;

    qCDebug(ModBusRtuMasterLog())<<__func__;
    m_SlaveDevList.append(Dev);//增加到支持的设备列表
    m_SlaveHash.insert(Dev->addr, Dev);//增加到设备地址，设备信息哈希表
    foreach(RegList_s reg_list, Dev->ReadRegList)
    {
        #if 0
        RegList_s *reg_l = &reg_list;
        if(reg_l->reg_info.type == "HoldReg")
        {
            qCDebug(ModBusRtuMasterLog())<<__func__<<"HoldReg:length"<<reg_l->reg_list.length();

            foreach(reg_s* reg, reg_l->reg_list)
            {
                m_HoldRegHash.insert(reg->reg_addr, reg);
            }
        }
        if(reg_l->reg_info.type == "InputReg")
        {
            foreach(reg_s* reg, reg_l->reg_list)
            {
                m_InputRegHash.insert(reg->reg_addr, reg);
            }
        }
#endif

    }
    return true;
}




// 初始化设备 这里的 pObj 是主站的设备信息
bool ModbusRtuMaster::initailizeDevice(void* pObj)
{
    qCDebug(ModBusRtuMasterLog())<<__func__;
    m_Dev = (Dev_s*)pObj;
    if(m_Dev)
    {
        /*"SerialPort,COM1,9600,N,8,1"*/
        QStringList port_list = m_Dev->port.split(',');
        QString port = port_list.at(1);
        int baud = port_list.at(2).toInt();
        int parity = 0;
        char pari = *port_list.at(3).toStdString().data();
        if(port_list.at(3) == "N")
        {
            parity = 0;
        }
        else if(port_list.at(3) == "E")
        {
            parity = 2;
        }
        else if(port_list.at(3) == "O")
        {
            parity = 3;
        }
        int data_bits = port_list.at(4).toInt();
        int stop_bit = port_list.at(5).toInt();

        qCDebug(ModBusRtuMasterLog())<<__func__<<port<<baud<<parity<<data_bits<<stop_bit;

#ifndef LIBMODBUS

        if (modbusDevice->state() != QModbusDevice::ConnectedState)
        {
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, baud);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, parity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, data_bits);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,stop_bit);
//            modbusDevice->setServerAddress(m_Dev->addr.toUInt());
//            connect(modbusDevice, &QModbusServer::dataWritten, this, &ModbusRtuMaster::dataWrittenSlot);

            modbusDevice->setTimeout(m_Dev->res_time);
            modbusDevice->setNumberOfRetries(1);
        }
        else
        {
//            return false;
        }
        return modbusDevice->connectDevice();
#else
        ctx = modbus_new_rtu(port.toStdString().data(), baud, pari, 8, 1);
        modbus_connect(ctx);
//        modbus_set_slave(ctx, SERVER_ID);
#endif

    }
    else
    {
//        qCDebug(ModbusRtuMasterLog())<<__func__<<"error";
        return false;
    }
    return true;
}

// 连接设备
bool ModbusRtuMaster::connectDevice(void* pObj){
    Q_UNUSED(pObj);
#ifndef LIBMODBUS
    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    return modbusDevice->connectDevice();
#endif
    return true;
}

// 断开设备连接
bool ModbusRtuMaster::disconnectDevice(void* pObj){
    Q_UNUSED(pObj);

#ifndef LIBMODBUS
    modbusDevice->disconnectDevice();
#endif

    return true;

}

// 反初始化设备
bool ModbusRtuMaster::unInitailizeDevice(void* pObj){
    Q_UNUSED(pObj);
    return true;
}


//获取发送报文
QByteArray ModbusRtuMaster::getSendFrame(){
}

//获取接收报文
QByteArray ModbusRtuMaster::getRevFrame(){

}



//设置 通讯通道
void ModbusRtuMaster::initComPort(ComPort *pPort)
{

}
