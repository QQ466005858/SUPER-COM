#include "ModBusRtuClient.h"
#include "ComShareMemory.h"


Q_LOGGING_CATEGORY(ModBusRtuClientLog, "DeviceLibrary.ModBusRtuClient.log")



//开始从机模式
void ModBusRtuClient::start(){
    qCDebug(ModBusRtuClientLog())<<__func__;
}

//停止
void ModBusRtuClient::stop(){
    qCDebug(ModBusRtuClientLog())<<__func__;
}

//打开通讯
void ModBusRtuClient::open(){
    qCDebug(ModBusRtuClientLog())<<__func__;
}

//关闭通讯端口
void ModBusRtuClient::close(){
    qCDebug(ModBusRtuClientLog())<<__func__;
}

//初始化 放到线程里
bool ModBusRtuClient::initialize(){


    modbusDevice = new QModbusRtuSerialSlave(this);

    return true;
}

//释放资源
bool ModBusRtuClient::uninitialize(){

    qCDebug(ModBusRtuClientLog())<<__func__;
    if (modbusDevice)
    {
        modbusDevice->disconnect();
        delete modbusDevice;
        modbusDevice = nullptr;
    }
    return true;
}

//判断设备的执行状态
bool ModBusRtuClient::isRunning(){
    qCDebug(ModBusRtuClientLog())<<__func__;
    return true;
}

//循环等待上位机 处理上位机的请求
bool ModBusRtuClient::doLoop(){
    qCDebug(ModBusRtuClientLog())<<__func__;

    static int cnt = 0;
    static reg_s tmp_reg;
    tmp_reg.id = QString::number( cnt);
    ComShareMemory::instance()->set_reg_by_index(0, tmp_reg);
    qCDebug(ModBusRtuClientLog())<<__func__<<"tmp_reg.id:"<<tmp_reg.id;


    ++cnt;
    return true;
}



//接收到设备更改的信号与槽
void ModBusRtuClient::receive_reg_data_slot(QList<reg_s*>reg_info_l, Dev_s* dev)
{
    if(!dev)
    {
        qCDebug(ModBusRtuClientLog())<<"#########"<<__func__<<"dev is null"<<"#########";
        return;
    }
    qCDebug(ModBusRtuClientLog())<<__func__<<"dev:"<<dev->id<<dev->name<<dev->port;

    qCDebug(ModBusRtuClientLog())<<__func__<<"reg_info_l:"<<reg_info_l.length();

    foreach(reg_s *reg_info, reg_info_l)
    {



        if(!reg_info)
        {
            qCDebug(ModBusRtuClientLog())<<__func__<<"reg_info Error null";
            return;
        }
        qCDebug(ModBusRtuClientLog())<<__func__<<"reg_info :"<<
                                    "id:"<<reg_info->id<<" "<<
                                    "name:"<<reg_info->name<<" "<<
                                    "type:"<<reg_info->type<<" "<<
//                                    "reg_val:"<<reg_info->reg_val.toInt()<<" "<<
                                    "reg_addr:"<< reg_info->reg_addr<<" "<<
                                    "related_id:"<<reg_info->related_id;

        #if 0
        //通过物理设备ID找到虚拟设备寄存器ID
        if(var_id == "")
        {
//            ComConfig::instance()->dump_PhyVirHash();
            qCDebug(ModBusRtuClientLog())<<__func__<<"var_id Error Not Find";
            return;
        }

        qCDebug(ModBusRtuClientLog())<<__func__<<"var_id:"<<var_id<<"reg_info:id"<<reg_info->id;

        if(!RegDev.pReg)
        {
            qCDebug(ModBusRtuClientLog())<<__func__<<"pRegDev Error null";
            return;
        }

        qCDebug(ModBusRtuClientLog())<<__func__<<reg_info->related_id;

        //寄存器赋值
        reg_s *pReg = RegDev.pReg;
        pReg->reg_val = reg_info->reg_val;
        //modbus 寄存器数据更改
        if(pReg->type == "HoldReg")
        {
            quint16 reg_data = pReg->reg_val.toInt();
            modbusDevice->setData(QModbusDataUnit::HoldingRegisters, pReg->reg_addr, reg_data);//寄存器默认数据为0 可能会修改
        }
        else if(pReg->type == "CoilsReg")
        {
            quint16 reg_data = pReg->reg_val.toInt();
            modbusDevice->setData(QModbusDataUnit::Coils, pReg->reg_addr, reg_data);//寄存器默认数据为0 可能会修改
        }
        else if(pReg->type == "InputReg")
        {
            quint16 reg_data = pReg->reg_val.toInt();
            modbusDevice->setData(QModbusDataUnit::InputRegisters, pReg->reg_addr, reg_data);//寄存器默认数据为0 可能会修改
        }
#endif
    }
}


// -- private

void ModBusRtuClient::setupDeviceData()
{
    if (!modbusDevice)
        return;
}


//增加设备 pObj 指向 Dev_s 指针结构体
bool ModBusRtuClient::additionDevice(void* pObj){

    qCDebug(ModBusRtuClientLog())<<__func__;
    if(pObj)
    {
        m_Dev = (Dev_s*)pObj;
        qCDebug(ModBusRtuClientLog())<<"m_Dev"<<m_Dev->name<<m_Dev->id<<m_Dev->port;
    }
    else
    {
        qCDebug(ModBusRtuClientLog())<<"pObj nullptr";
        return false;
    }

    if(modbusDevice == nullptr)
    {
        modbusDevice = new QModbusRtuSerialSlave(this);
    }
#if 0
    foreach(RegList_s reg_list, m_Dev->ReadRegList)
    {
        QModbusDataUnitMap reg;
        int reg_start = reg_list.reg_info.reg_start;
        int reg_end   = reg_list.reg_info.reg_end;
        quint16 reg_num = reg_end - reg_start + 1;
        QVector<quint16> RegBuf;
        RegBuf.resize(reg_num);
        if( reg_list.reg_info.type == "HoldReg")
        {
            qCDebug(ModBusRtuClientLog())<<__func__<<"HoldReg:"<<reg_start<<reg_num;
            reg.insert(QModbusDataUnit::HoldingRegisters,  { QModbusDataUnit::HoldingRegisters, reg_start, reg_num });
            modbusDevice->setMap(reg);
            for(int i=0; i<reg_num;i++)
            {
                int reg_set_addr = reg_start + i;
                //设置寄存器Map 之后需要初始化 数据 否则 会出现召测不成功的现象
                modbusDevice->setData(QModbusDataUnit::HoldingRegisters, reg_set_addr, 0);//寄存器默认数据为0 可能会修改
            }
        }
        else if( reg_list.reg_info.type == "InputReg")
        {
            reg.insert(QModbusDataUnit::HoldingRegisters,  { QModbusDataUnit::InputRegisters, reg_start, reg_num });
        }
        else if( reg_list.reg_info.type == "DiscrtReg")
        {
            reg.insert(QModbusDataUnit::HoldingRegisters,  { QModbusDataUnit::DiscreteInputs, reg_start, reg_num });
        }
        else if( reg_list.reg_info.type == "CoilsReg")
        {
            reg.insert(QModbusDataUnit::HoldingRegisters,  { QModbusDataUnit::Coils, reg_start, reg_num });
        } 
    }
#endif

//    foreach(RegList_s *reg_list, m_Dev->WriteRegList)
//    {
//        QModbusDataUnitMap reg;
//        int reg_start = reg_list.reg_info->reg_start;
//        int reg_end   = reg_list.reg_info->reg_end;
//        quint16 reg_num = reg_end - reg_start + 1;
//        if( reg_list.reg_info->type == "CoilsReg")
//        {
//            reg.insert(QModbusDataUnit::HoldingRegisters,  { QModbusDataUnit::Coils, reg_start, reg_num });
//            modbusDevice->setMap(reg);
//        }
//        else if( reg_list.reg_info->type == "HoldReg")
//        {
//            reg.insert(QModbusDataUnit::HoldingRegisters,  { QModbusDataUnit::HoldingRegisters, reg_start, reg_num });
//            modbusDevice->setMap(reg);
//            for(int i=0; i<reg_num;i++)
//            {
//                int reg_set_addr = reg_start + i;
//                modbusDevice->setData(QModbusDataUnit::HoldingRegisters, reg_set_addr, 0);//寄存器默认数据为0 可能会修改
//            }
//        }
//    }
    return true;
}

void ModBusRtuClient::testSlot(QString slot)
{
    qCDebug(ModBusRtuClientLog())<<__func__<<slot;
}


//接收到上位机写数据的槽  需要 发送数据改变信号
void ModBusRtuClient::dataWrittenSlot(QModbusDataUnit::RegisterType table, int address, int size)
{
//    modbusDevice->serverAddress();

    qCDebug(ModBusRtuClientLog())<<__func__;
#if 0

    QList<reg_s*>tmp_write_reg_l;
    for (int i = 0; i < size; ++i) {
        int reg_addr = address + i;
        quint16 value;
        switch (table) {
        //写线圈
        case QModbusDataUnit::Coils:
            modbusDevice->data(QModbusDataUnit::Coils, reg_addr, &value);
            foreach(RegList_s reg_list, m_Dev->WriteRegList)
            {
                if(reg_list.reg_info->type == "CoilsReg")
                {
                    foreach(reg_s reg, reg_list.reg_list)
                    {
                        if(reg.reg_addr == reg_addr)
                        {
                            //如果找到对应的寄存器
                            reg.reg_val = value;//寄存器值复制
                            QString phy_id =  ComRes.instance()->GetPhyIdByVirId(reg.id);
                            reg_dev_s *pDevReg = ComRes.instance()->GetRegInfoByID(phy_id);
                            pDev.reg.pReg->.rev_write_val = reg.reg_val;//赋值寄存器要写入的值
                            //触发写寄存器信号 多个槽收到 需要增加判定
                            tmp_write_reg_l.append(pDevreg.pReg);
                            emit report_reg_data_signal(tmp_write_reg_l, pDevreg.pDev);
                        }
                    }
                }
            }
            break;
            //写保持寄存器
        case QModbusDataUnit::HoldingRegisters:
            modbusDevice->data(QModbusDataUnit::HoldingRegisters, reg_addr, &value);
            foreach(RegList_s *reg_list, m_Dev->WriteRegList)
            {
                if(reg_list.reg_info->type == "HoldReg")
                {
                    foreach(reg_s *reg, reg_list.reg_list)
                    {
                        if(reg.reg_addr == reg_addr)
                        {
                            //如果找到对应的寄存器
                            reg.reg_val = value;//寄存器值复制
//                            emit report_reg_data_signal(reg);
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }

#endif

}


// 初始化设备
bool ModBusRtuClient::initailizeDevice(void* pObj)
{
    Q_UNUSED(pObj);
    qCDebug(ModBusRtuClientLog())<<__func__;
    if(m_Dev)
    {
        /*"SerialPort,COM1,9600,N,8,1"*/
        QStringList port_list = m_Dev->port.split(',');


        QString port = port_list.at(1);
        int baud = port_list.at(2).toInt();

        int parity = 0;
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
        qCDebug(ModBusRtuClientLog())<<__func__<<port<<baud<<parity<<data_bits<<stop_bit;


//        if (modbusDevice->state() != QModbusDevice::ConnectedState)
//        {
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, baud);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, parity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, data_bits);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,stop_bit);
            modbusDevice->setServerAddress(m_Dev->addr);
//            connect(modbusDevice, &QModbusServer::dataWritten, this, &ModBusRtuClient::dataWrittenSlot);
//        }
//        else
//        {
////            return false;
//        }
        return modbusDevice->connectDevice();
    }
    else
    {
        qCDebug(ModBusRtuClientLog())<<__func__<<"error";
        return false;
    }
}

// 连接设备
bool ModBusRtuClient::connectDevice(void* pObj){
    Q_UNUSED(pObj);
    return true;
}

// 断开设备连接
bool ModBusRtuClient::disconnectDevice(void* pObj){
    Q_UNUSED(pObj);
    return true;

}

// 反初始化设备
bool ModBusRtuClient::unInitailizeDevice(void* pObj){
    Q_UNUSED(pObj);
    return true;
}


//获取发送报文
QByteArray ModBusRtuClient::getSendFrame(){

}

//获取接收报文
QByteArray ModBusRtuClient::getRevFrame(){

}



//设置 通讯通道
void ModBusRtuClient::initComPort(ComPort *pPort)
{

}



#if 0
//读寄存器列表
int ModBusRtuClient::readRegList(RegList_s *pRegList){

}

//读单个寄存器
bool ModBusRtuClient::readReg(Reg_Info_s info, reg_s *pReg){

}

//写寄存器列别
int ModBusRtuClient::writeRegList(RegList_s *pRegList){

}

//写单个寄存器
bool ModBusRtuClient::writeReg(Reg_Info_s info, reg_s *pReg){

}

// 写变量前处理
bool ModBusRtuClient::beforeWriteReg(void* pObj, reg_s* pReg){

}

// 写变量后处理
bool ModBusRtuClient::afterWriteReg(void* pObj, reg_s* pReg){

}

// 读变量前处理
bool ModBusRtuClient::beforeReadReg(void* pObj, reg_s* ){

}

// 读变量后处理
bool ModBusRtuClient::afterReadReg(void* pObj, reg_s* pReg){

}

//主动上报寄存器信息
bool ModBusRtuClient::reportRegList(RegList_s *pRegList){

}

//上报单个寄存器
bool ModBusRtuClient::reportReg(Reg_Info_s info, reg_s *pReg){

}
#endif

