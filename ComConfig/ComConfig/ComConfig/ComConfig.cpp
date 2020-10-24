#include "ComConfig.h"
#include <QDomDocument>


//ComConfig ComResData;

/*
 * 配置文件中的名称解析定义
*/
const QString PhyDevListTagName = "PhyDevList";
const QString VirDevListTagName = "VirDevList";
const QString ReadListTagName = "ReadList";
const QString WriteListTagName = "WriteList";
const QString ReportListTagName = "ReportList";
const QString ReadWriteListTagName = "ReadWriteList";
const QString ReadRegListRegName = "ReadRegList";
const QString WriteRegListRegName = "WriteRegList";
const QString ReportListRegName = "ReportRegList";
const QString ReadWriteListRegName = "ReadWriteRegList";
const QList<QString>m_RegListTagName = {ReadListTagName,WriteListTagName,ReportListTagName,ReadWriteListTagName};
const QList<QString>m_RegListRegName = {ReadRegListRegName,WriteRegListRegName,ReportListRegName,ReadWriteListRegName};


QHash<QString , QString >  m_RegIdPhyVirHash;//ID关联HASH KEY:PhyDev ID VAL：VirDev ID
QHash<QString , QString >  m_RegIdVirPhyHash;//ID关联HASH KEY: VirDev   ID VAL：PhyDev ID
QHash<QString, reg_dev_s>  m_RegIdRegInfoHash;//根据寄存器ID找实例化寄存器值


QList<Dev_s*> ComConfig::m_PhyDevList;//要接的物理设备的列表
QList<Dev_s*> ComConfig::m_VirDevList;//要转发的设备列表
QMap<QString , Dev_s> ComConfig::m_IdDevMap;//根据ID找设备
QDomDocument ComConfig::m_doc;//读取XML使用
QDomElement ComConfig::m_root;//根节点
super_com_info_s ComConfig::m_super_com_info;//通讯管理机信息
QList <reg_s>ComConfig::m_RegList;//全部寄存器的列表
QHash <QString, QList<Dev_s>>ComConfig::m_PortDevListHash;//保留端口和对应设备的Hash表信息


Q_LOGGING_CATEGORY(ComConfigLog, "ComConfig.log")

#define CONFIG_FILE_PATH  "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml"

ComConfig::ComConfig()
{
    qCDebug(ComConfigLog())<<"ComConfig 构造";
//    ReadXml(CONFIG_FILE_PATH);
}
ComConfig::~ComConfig()
{
    qCDebug(ComConfigLog())<<"ComConfig 析构";
}


void ComConfig::dumpRegInfoHash()
{
    qCDebug(ComConfigLog())<<__func__;

    QHash<QString, reg_dev_s>::const_iterator i;
    for (i = m_RegIdRegInfoHash.constBegin(); i != m_RegIdRegInfoHash.constEnd(); ++i) {
        qCDebug(ComConfigLog())<<__func__<< i.key() << ":" << i.value().pReg->id;

    }
}

void ComConfig::dump_PhyVirHash()
{
    qCDebug(ComConfigLog())<<__func__<<m_RegIdPhyVirHash.size()<<m_RegIdPhyVirHash.keys();


    QHash<QString, QString>::const_iterator i;
    for (i = m_RegIdPhyVirHash.constBegin(); i != m_RegIdPhyVirHash.constEnd(); ++i) {
        qCDebug(ComConfigLog())<<__func__<< i.key() << ":" << i.value();

    }
}
void ComConfig::dump_VirPhyHash()
{
    qCDebug(ComConfigLog())<<__func__;

    QHash<QString, QString>::const_iterator i;
    for (i = m_RegIdVirPhyHash.constBegin(); i != m_RegIdVirPhyHash.constEnd(); ++i) {
        qCDebug(ComConfigLog())<<__func__<< i.key() << ":" << i.value();

    }
}

void ComConfig::dump_PortDevListHash()
{
    qCDebug(ComConfigLog())<<__func__;
    QHash <QString, QList<Dev_s> >::const_iterator i;//保留端口和对应设备的Hash表信息
    for (i = m_PortDevListHash.constBegin(); i != m_PortDevListHash.constEnd(); ++i) {
        qCDebug(ComConfigLog())<<__func__<< i.key();
        QList<Dev_s> tmp_dev_list = i.value();
        foreach(Dev_s dev, tmp_dev_list)
        {
            qCDebug(ComConfigLog())<<"dev:"<<dev.id<<dev.name<<dev.port;
        }
    }
}



//读xml
bool ComConfig::ReadXml(QString f_name)
{
    clearConfigInfoContain();

    //每次读取XML必须清空list

    //打开或创建文件
    QFile file(f_name); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly)){
        qCDebug(ComConfigLog())<<"Config File Not exist!";
        return false;
    }
    if(!m_doc.setContent(&file))
    {
        qCDebug(ComConfigLog())<<"Config File Formate Error!";
        file.close();
        return false;
    }
    file.close();
    //考虑做一个调试信息获取接口
    m_root = m_doc.documentElement(); //返回根节点 获取根节点信息
    m_super_com_info.info = m_root.attribute("info");
    m_super_com_info.date_time = m_root.attribute("date_time");
    m_super_com_info.version = m_root.attribute("version");

    qCDebug(ComConfigLog())<<"m_root.nodeName:"<<m_root.nodeName();

    QDomNodeList list = m_root.childNodes();
    for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
    {
        QDomNode n = list.at(i);
        readAllDevList(n.toElement());
    }

    return  true;
}

//ele 为 节点 PhyDevList 或者 VirDevList
bool ComConfig::readAllDevList(const QDomElement &ele)
{
    if(ele.tagName() == PhyDevListTagName || ele.tagName() == VirDevListTagName )
    {
        //qCDebug(ComConfigLog)<<"readAllDevList:tagName:"<<ele.tagName();
        QList<Dev_s*> *pDevList = GetDevListByTagName(ele.tagName());
        if(pDevList == nullptr)
        {
            qCWarning(ComConfigLog())<<__func__<<"GetDevListByTagName:"<<"###########ERROR###########";
            return false;
        }
        QDomNodeList list = ele.childNodes();
        for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
        {

            Dev_s *tmp_Dev = new Dev_s();

            tmp_Dev->ReadRegList.clear();
            tmp_Dev->WriteRegList.clear();

            QDomNode n = list.at(i);
            tmp_Dev->type = n.toElement().attribute("type");
            tmp_Dev->port = n.toElement().attribute("port");
            tmp_Dev->addr = n.toElement().attribute("addr").toUInt();
            tmp_Dev->id = n.toElement().attribute("id").toUInt();
            tmp_Dev->bOnline = n.toElement().attribute("bOnline") == "true" ? true : false;
            tmp_Dev->name = n.toElement().attribute("name");
            tmp_Dev->DeviceLibrary = n.toElement().attribute("DeviceLibrary");
            tmp_Dev->res_time = n.toElement().attribute("res_time").toUInt();
            QDomNodeList reg_list = n.toElement().childNodes();
            qCDebug(ComConfigLog)<<"readAllDevList:tmp_Dev: type"<<tmp_Dev->type
                                <<"port:"<<tmp_Dev->port
                               <<"id:"<<tmp_Dev->id<<"DeviceLibrary:"<<tmp_Dev->DeviceLibrary ;
//            qCDebug(ComConfigLog)<<"list :"<<n.toElement().tagName()<<"i:"<<i << "reg_list.count:"<<reg_list.count();

            for(int j=0; j<reg_list.count(); j++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode reg = reg_list.at(j);
                if( m_RegListTagName.indexOf(reg.toElement().tagName()) != -1)
                {
                    QDomNodeList read_reg_list = reg.toElement().childNodes();
                    QList<RegList_s>  *pRegList_s = tmp_Dev->GetRegListByTagName(reg.toElement().tagName());
//                    qCDebug(ComConfigLog)<<"read_reg_list.count :"<<read_reg_list.count()<<"j:"<<j;

                    for(int k=0; k<read_reg_list.count(); k++)
                    {
                        QDomNode RegList_n = read_reg_list.at(k);
                        qCDebug(ComConfigLog)<<"RegList_n :"<<RegList_n.toElement().tagName()<<"k:"<<k;

//                        RegList_s *tmp_read_reg_list = new RegList_s();
                        RegList_s tmp_read_reg_list;

                        if(m_RegListRegName.indexOf(RegList_n.toElement().tagName()) != -1)
                        {
                            tmp_read_reg_list.reg_info.type = RegList_n.toElement().attribute("type").toUInt();
                            tmp_read_reg_list.reg_info.mode = RegList_n.toElement().attribute("mode");
                            //寄存器地址默认按16进制
                            tmp_read_reg_list.reg_info.reg_start = RegList_n.toElement().attribute("reg_start").toUInt(nullptr, 16);
                            tmp_read_reg_list.reg_info.reg_end = RegList_n.toElement().attribute("reg_end").toUInt(nullptr, 16);
                            tmp_read_reg_list.reg_info.group_name = RegList_n.toElement().attribute("group_name");
                            tmp_read_reg_list.reg_info.read_flag = RegList_n.toElement().attribute("read_flag") == "true"? true:false;
                            tmp_read_reg_list.reg_info.reg_num = RegList_n.toElement().attribute("reg_num").toUInt();
                            tmp_read_reg_list.reg_info.block_read = RegList_n.toElement().attribute("block_read") == "true" ? true:false;
                            tmp_read_reg_list.reg_info.poll_wait = RegList_n.toElement().attribute("poll_wait").toUInt();
                            tmp_read_reg_list.reg_info.block_write = RegList_n.toElement().attribute("block_write") == "true" ? true:false;

                            QDomNodeList reg_list = RegList_n.toElement().childNodes();

                            qCDebug(ComConfigLog)<<"readAllDevList:reg_info:type"<<tmp_read_reg_list.reg_info.type;

                            for(int l=0; l<reg_list.count(); l++)
                            {
                                QDomNode Reg_n = reg_list.at(l);
                                QDomElement Reg_e = Reg_n.toElement();
                                reg_s *tmp_reg = new reg_s();
//                                reg_s pRegData ;
                                reg_s & pRegData = *tmp_reg;
                                pRegData.addr_base = Reg_e.attribute("addr_base").toUInt() == 0 ? 16 : Reg_e.attribute("addr_base").toUInt();
                                pRegData.reg_addr = Reg_e.attribute("reg_addr").toUInt(nullptr, pRegData.addr_base);
                                pRegData.name = Reg_e.attribute("name");

//                                memcpy(pRegData.name, Reg_e.attribute("name").toStdString().data(), Reg_e.attribute("name").length());

                                pRegData.unit = Reg_e.attribute("unit");
//                                memcpy(pRegData.unit, Reg_e.attribute("unit").toStdString().data(), Reg_e.attribute("unit").length());


                                pRegData.reg_type = Reg_e.attribute("reg_type").toUInt();
                                pRegData.dis_type = Reg_e.attribute("dis_type").toUInt();
                                pRegData.mult_val = Reg_e.attribute("mult_val").toDouble();
                                pRegData.dec_bit = Reg_e.attribute("dec_bit").toUInt();
                                pRegData.id = Reg_e.attribute("id").toUInt();
                                pRegData.record = Reg_e.attribute("record") == "true" ? true:false;
                                pRegData.related_id = Reg_e.attribute("related_id").toUInt();
                                pRegData.block_index = Reg_e.attribute("block_index").toUInt();

                                //增加寄存器类型 2020-7-29 15:40:01
                                pRegData.type = tmp_read_reg_list.reg_info.type;//设置寄存器类型
                                //物理设备没有 related_id
                                if(pRegData.related_id.length())
                                {
//                                    qCDebug(ComConfigLog)<<"pRegData.id:"<<pRegData.id<<"pRegData.related_id:"<<pRegData.related_id;
                                    m_RegIdVirPhyHash.insert(pRegData.id, pRegData.related_id);
                                    m_RegIdPhyVirHash.insert(pRegData.related_id, pRegData.id);
                                }


                                tmp_read_reg_list.reg_list.append(pRegData);

                                //增加 地址 和 寄存器数据对应
//                                tmp_read_reg_list.reg_hash.insert(pRegData.reg_addr, pRegData);

//                                pRegHash_s->insert(pRegData.reg_addr, pRegData);

                                qCDebug(ComConfigLog)<<"readAllDevList: tmp_reg:reg_addr"<<pRegData.reg_addr <<"name:"<<
                                                       pRegData.name;
                                reg_dev_s RegDev;
                                RegDev.pDev = tmp_Dev;
                                RegDev.pReg = &pRegData;
                                //2020-7-29 15:25:33 增加
                                m_RegIdRegInfoHash.insert(pRegData.id, RegDev);


                                //2020-8-13 21:25:07
                                m_RegList.append(pRegData);//添加每一个寄存器
                            }
                            pRegList_s->append(tmp_read_reg_list);
                        }
                        else
                        {
                            qCDebug(ComConfigLog)<<"RegList_n :tagName "<<RegList_n.toElement().tagName()<<"k:"<<k;
                        }
                    }
                }
                else
                {
                }
            }

            pDevList->append(tmp_Dev);
            //m_IdDevMap.insert(tmp_Dev->id, tmp_Dev);
            QString key = tmp_Dev->id;
            Dev_s tmp_dev_s = *tmp_Dev;
            m_IdDevMap.insert(key, tmp_dev_s);
            qCDebug(ComConfigLog())<<__func__<<"pDevList len "<<pDevList->length();

            QString tmp_port = tmp_dev_s.port;
            QList<Dev_s> & hash_dev = m_PortDevListHash[tmp_port];
            hash_dev.append(tmp_dev_s);
            m_PortDevListHash.insert(tmp_port, hash_dev);
        }
    }
    else
    {
        return  false;
    }
    return true;
}
