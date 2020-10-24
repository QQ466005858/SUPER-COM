#include "ComShareMemory.h"

Q_LOGGING_CATEGORY(ComShareMemoryLog, "ComShareMemoryLog.ComShareMemoryLog.log")



ComShareMemory::ComShareMemory(QString key, QObject *parent):
    QSharedMemory(key, parent)
{
    setKey(key);
    m_Key = QSharedMemory::key();
    qCDebug(ComShareMemoryLog())<<__func__<<"构造"<<"key:"<<m_Key;

}
static void dump_dev(Dev_s &dev)
{
    qCDebug(ComShareMemoryLog())<<__func__<<"dev:name"<<dev.name
                               <<"port:"<<dev.port;

    foreach(RegList_s reg_list, dev.ReadRegList)
    {
        qCDebug(ComShareMemoryLog())<<reg_list.reg_info.mode
                                  <<reg_list.reg_info.reg_num;
        foreach(reg_s reg, reg_list.reg_list)
        {
            qCDebug(ComShareMemoryLog())<<reg.id<<reg.name<<reg.mult_val;
        }
    }
}

#if 1

bool ComShareMemory::create_share_memory(int size)
{
    qCDebug(ComShareMemoryLog())<<__func__<<"size:"<<size;
    return create(size);
}



//根据寄存器列表初始化共享内存
bool ComShareMemory::init_share_memory(QList<reg_s> &regList)
{
    int mem_size = regList.length() * sizeof(reg_s);
    int test_size = sizeof(regList);
    qCDebug(ComShareMemoryLog())<<__func__<<"regList.length:"<<regList.length()<<"mem_size:"<<mem_size<<"test_size:"<<test_size;
    bool res = create_share_memory(mem_size);//创建共享内存

    if(!res)
    {
        qCDebug(ComShareMemoryLog())<<__func__<<"Memory Malloc  Failed!";
        return false;
    }
    res = attach();
    qCDebug(ComShareMemoryLog())<<__func__<<"Memory Malloc  OK!"<<"size:"<<size()<<"res:"<<res<<"sizeof(reg_s):"<<sizeof(reg_s);

    lock();

    //获取共享数据指针
    reg_s *p_reg_s = static_cast<reg_s*>(data());
    for(int i=0; i<regList.length(); i++)
    {
        memcpy((void*)&p_reg_s[i], &regList[i], sizeof(reg_s) );

        p_reg_s[i] = regList.at(i);
    }

    for(int i=0; i<regList.length(); i++)
    {
        if(p_reg_s[i].id != regList.at(i).id)
        {
            goto FAILED;
        }
    }

    //detach();  detach 会释放内存
    unlock();
    qCDebug(ComShareMemoryLog())<<__func__<<"Memory Malloc and Test Ok!";

    return true;
    FAILED:
    detach();
    unlock();

    qCDebug(ComShareMemoryLog())<<__func__<<"Memory Malloc Ok But Test Failed!";

    return false;

}

//通过寄存器索引设置内存
bool ComShareMemory::set_reg_by_index(int index, reg_s &reg)
{
    QSharedMemory   sharedMem;
     sharedMem.setKey(m_Key);
     bool res = sharedMem.attach(QSharedMemory::ReadWrite);
     if (!res) {
         return false;
     }
    sharedMem.lock();
    reg_s * p_reg = static_cast<reg_s*>(sharedMem.data());
    sharedMem.unlock();
    p_reg[index] = reg;
    sharedMem.unlock();
    return true;
}

//通过REG的index返回内存中的reg 信息的复制品
reg_s ComShareMemory::get_reg_by_index(int index)
{
    reg_s tmp;
    QSharedMemory   sharedMem;
     sharedMem.setKey(m_Key);
     bool res = sharedMem.attach(QSharedMemory::ReadWrite);
     if (!res) {
         return tmp;
     }
    sharedMem.lock();
    reg_s * p_reg = static_cast<reg_s*>(sharedMem.data());
    sharedMem.unlock();
    tmp = p_reg[index];
    sharedMem.unlock();
    return tmp;
}


//创建设备信息的共享内存
bool ComShareMemory::creat_dev_info_mem(Dev_s &dev)
{
    QString key = dev.GetDevKey();
    QSharedMemory sharedMem(key);

    qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key;
//    sharedMem.setKey(key);
    if( sharedMem.create(sizeof(dev)) == false)
    {
        qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key<<"共享内存创建失败"<<"sizeof(dev):"<<sizeof(dev);
    }
    else
    {
        qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key<<"共享内存创建成功"<<"sizeof(dev):"<<sizeof(dev);
    }

//    sharedMem.lock();
    if(!sharedMem.isAttached())
    {
        bool res = sharedMem.attach();
        qCDebug(ComShareMemoryLog())<<__func__<<"res:"<<res<<"isAttached:"<<sharedMem.isAttached();
    }
//    if (!res) {
//        sharedMem.detach();
//        qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key<<"共享内存attach失败"<<"sizeof(dev):"<<sizeof(dev);
//        return false;
//    }
    Dev_s * pDev = static_cast<Dev_s*>(sharedMem.data());
    memcpy((void*)pDev, &dev, sizeof(dev));
    *pDev = dev;


    qCDebug(ComShareMemoryLog())<<__func__<<"pDev:";

    dump_dev(*pDev);
//    sharedMem.unlock();
    qCDebug(ComShareMemoryLog())<<__func__<<"ok";

    m_DevKeyList.append(dev.GetDevKey());//添加到设备key值列表
    return true;
}
#endif

bool ComShareMemory::CreatDevListMem(QString key, QList<Dev_s>&DevList)
{
    QSharedMemory *pQSharedMemory = new QSharedMemory(key);
    QSharedMemory &sharedMem = *pQSharedMemory;

    qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key;
    int size = DevList.length() * sizeof(Dev_s);

    if( sharedMem.create(size, QSharedMemory::ReadWrite) == false)
    {
        qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key<<"共享内存创建失败"<<"size:"<<size;
    }
    else
    {
        qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key<<"共享内存创建成功"<<"size:"<<size<<"DevList:size"<<sizeof (DevList);
    }
    sharedMem.attach();
    if(!sharedMem.isAttached())
    {
//        sharedMem.attach();
        qCDebug(ComShareMemoryLog())<<__func__<<"key:"<<key<<"共享内存attach失败"<<"size:"<<size;
    }
    Dev_s * pDev = static_cast<Dev_s*>(sharedMem.data());
    sharedMem.lock();
    for(int i=0; i<DevList.length(); i++)
    {
        memcpy((void*)&pDev[i], &DevList[i], sizeof(Dev_s));
//        pDev[i] = DevList[i];
        dump_dev(*pDev);
    }
    sharedMem.unlock();
    qCDebug(ComShareMemoryLog())<<__func__<<"ok";
    return true;
}



