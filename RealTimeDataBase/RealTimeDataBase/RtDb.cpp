#include "RtDb.h"


RtDb::RtDb()
{

}
RtDb::~RtDb()
{

}


QVariant RtDb::GetData(const QString &id)
{
    return m_RegDataHash[id];
}
QString RtDb::GetDataString(const QString &id)
{

}
void RtDb::SetData(const QString &id, QVariant dat)
{
    m_RegDataHash.insert(id, dat);//设置id 和数据
}
void RtDb::SetDataString(const QString &id, const QString &dat)
{

}
void RtDb::SetDataStringInner(const QString &id, const QString &dat)
{

}
QString RtDb::getIdByTagName(const QString &name)
{

}
void RtDb::debug()
{

}
void RtDb::debugShowNameMapId()
{

}
// 从共享内存取一个未使用的DBTagObject对象
//PDBTagObject getEmptyDBTagObject();
// 添加需要写入PLC或仪器的变量至相应设备节点写队列
void RtDb::addNeedWriteTagToDeviceWriteQueue()
{

}
