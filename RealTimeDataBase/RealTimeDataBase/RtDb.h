#ifndef RTDB_H
#define RTDB_H

#include <QObject>
#include <QHash>

#include "ComConfig.h"
//class RtDbBase
//{
//public:
//    virtual ~RtDbBase(){};
//};


class RtDb : public QObject
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "RealTimeDataBase.RealTimeDataBaseLibrary.RtDb" FILE "RealTimeDataBaseLibrary.json")
public:
    static RtDb *instance() {
        static RtDb rtdb;
        return &rtdb;
    }
public:
    RtDb();
    ~RtDb();
public:
    QVariant GetData(const QString &id);
    QString GetDataString(const QString &id);
    void SetData(const QString &id, QVariant dat);
    //void SetTypeAndData(const QString &id, TTagDataType type, TAny dat);
    void SetDataString(const QString &id, const QString &dat);
    void SetDataStringInner(const QString &id, const QString &dat);
    QString getIdByTagName(const QString &name);
    void debug();
    void debugShowNameMapId();
    // 从共享内存取一个未使用的DBTagObject对象
    //PDBTagObject getEmptyDBTagObject();
    // 添加需要写入PLC或仪器的变量至相应设备节点写队列
    void addNeedWriteTagToDeviceWriteQueue();


private:
    QHash<QString , QVariant > m_RegDataHash;//KEY:ID(寄存器ID) VAL:寄存器
};

#endif // RTDB_H
