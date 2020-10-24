#ifndef COMSHAREMEMORY_H
#define COMSHAREMEMORY_H

#include "ComShareMemory_global.h"
#include "QSharedMemory"
#include "ComConfig.h"
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(ComShareMemoryLog)

class ComShareMemory : public QSharedMemory
{
public:
    static ComShareMemory *instance()
    {
        static ComShareMemory share;
        return & share;
    }
public:
    ComShareMemory(QString key="ComShareMemory", QObject *parent = nullptr);
    bool CreatDevListMem(QString key, QList<Dev_s>&DevList);
private:
    bool create_share_memory(int size = 0);
    QString m_Key;
    QList<QString>m_DevKeyList;



    /****************测试使用***********/
public:
    bool init_share_memory(QList<reg_s> & regList);
    bool set_reg_by_index(int index, reg_s &reg);
    reg_s get_reg_by_index(int index);
    bool creat_dev_info_mem(Dev_s &dev);//创建设备信息的共享内存


};

#endif // COMSHAREMEMORY_H
