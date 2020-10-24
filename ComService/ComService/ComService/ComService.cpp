#include "ComService.h"


//ComConfig *pComConfig = ComConfig::instance();
//ComShareMemory *pComShareMemory = ComShareMemory::instance();


Q_LOGGING_CATEGORY(ComServiceLog, "ComService.log")


ComService::ComService(QObject *parent) : QObject(parent)
{
    qCDebug(ComServiceLog())<<__func__<<"构造";
}

ComService::~ComService()
{
    qCDebug(ComServiceLog())<<__func__<<"析构";
}

/*
 * 2020-8-18 21:18:39
 * 加载服务配置
*/
bool ComService::Load(QString cfg_xml)
{
    //先加载配置文件
    bool res = m_ComConfig.ReadXml(cfg_xml);
    if(!res)
        return res;

    //配置文件加载完成后建立设备信息的共享内存
    QHash <QString, QList<Dev_s> > & tmp_DevListHash = m_ComConfig.GetPortDevListHash();
    QHash <QString, QList<Dev_s> >::iterator i;
    for(i=tmp_DevListHash.begin(); i!=tmp_DevListHash.end(); ++i)
    {
        m_ComShareMemory.CreatDevListMem(i.key(), i.value());
    }
    return true;
}
