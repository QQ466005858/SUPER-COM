#ifndef COMCONFIG_H
#define COMCONFIG_H

#include <QObject>
#include <QHash>
#include <QFile>
#include <QMap>
#include <QDomDocument>
#include <QSharedMemory>


#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(ComConfigLog)


#define REG_NAME_LEN    32  //寄存器名称长度
#define UNIT_LEN        8   //单位长度
#define REG_VAL_LEN     32   //单个寄存器数据长度

//寄存器结构体保存单个寄存器详细信息
struct reg_s
{
    int reg_addr;
    int addr_base;
//    char name[REG_NAME_LEN] = {0};
//    char unit[UNIT_LEN]= {0};
    QString name;
    QString unit;
    QString reg_type;//寄存器类型，  ushort short bool
    double mult_val;
    int dec_bit;
    QString id;
    bool record;
    //QString val;
    QString time;//采集的时间 时间戳
    QString dis_type;
    QString related_id;//关联物理设备ID  //虚拟设备使用
    int block_index;

//    char reg_val[REG_VAL_LEN]= {0};//寄存器值
//    char rev_write_val[REG_VAL_LEN]= {0};//寄存器要写入的值
    QVariant reg_val;
    QVariant rev_write_val;
    bool b_reg_write = false;//寄存器写入成功标记
    int type;//寄存器类型
};

class Reg : public QObject
//class Reg
{
    Q_OBJECT
public:
    Reg(){};
    ~Reg(){};
    reg_s reg;
signals:
    void test();
public slots:
    void test_slot()
    {

    }
//    const Reg operator + (const Reg& c) const{
////        Reg res();
////        return res;
//    }

};


Q_DECLARE_METATYPE(reg_s)

//寄存器组信息用于保留这个寄存器所属的组的信息
struct Reg_Group_Info_s
{
    int type;
    QString mode;
    int reg_start;
    int reg_end;
    QString group_name;
    bool read_flag;
    int reg_num;
    bool block_read;
    bool block_write;
    int poll_wait;
};
Q_DECLARE_METATYPE(Reg_Group_Info_s)


//寄存器列表
struct RegList_s
{
    Reg_Group_Info_s reg_info;
    QList<reg_s>reg_list;
};

Q_DECLARE_METATYPE(RegList_s)


#define PhyDev "PhyDev"
#define VirDev "VirDev"


//设备结构体 用于描述设备信息和寄存器信息
struct Dev_s
{
    QString port;
    int addr;
    QString id;
    QString type;//设备类型
    bool bOnline = false;
    QString name;
    QString DeviceLibrary;
    int res_time = 2000;

    QList<RegList_s>ReadRegList;
    QList<RegList_s>WriteRegList;
    QList<RegList_s>ReportRegList;

    QString ReadListTagName = "ReadList";
    QString WriteListTagName = "WriteList";
    QString ReportListTagName = "ReportList";
    QString ReadWriteListTagName = "ReadWriteList";


    QList<RegList_s> *GetRegListByTagName(QString name)
    {
        if(name == ReadListTagName)
        {
            return &ReadRegList;
        }
        else if(name == WriteListTagName)
        {
            return &WriteRegList;
        }
        else if(name == ReportListTagName)
        {
            return &ReportRegList;
        }
        return nullptr;
    }
    QString GetDevKey()
    {
        return name + ":" +id;
    }
    //    QHash<int , reg_s*>ReadRegHash;//根据寄存器地址获取寄存器数据
    //    QHash<int , reg_s*>WriteRegHash;//根据寄存器地址获取寄存器数据
    //    QHash<int , reg_s*>ReportRegHash;//根据寄存器地址获取寄存器数据
//    QHash<int , reg_s*> *GetRegHashByTagName(QString name)
//    {
//        if(name == ReadListTagName)
//        {
//            return &ReadRegHash;
//        }
//        else if(name == WriteListTagName)
//        {
//            return &WriteRegHash;
//        }
//        else if(name == ReportListTagName)
//        {
//            return &ReportRegHash;
//        }
//        return nullptr;
//    }

};
Q_DECLARE_METATYPE(Dev_s)

struct super_com_info_s
{
    QString info;
    QString date_time;
    QString version;
};
Q_DECLARE_METATYPE(super_com_info_s)


//寄存器-设备结构体
struct reg_dev_s
{
    reg_s *pReg ;//寄存器
    Dev_s *pDev;//该寄存器所属的设备
};
Q_DECLARE_METATYPE(reg_dev_s)


//class DevInfo
//{
//public:
//    DevInfo(){};
//    ~DevInfo(){};

//private:
//    Dev_s mDev;
//};


extern const QString PhyDevListTagName;
extern const QString VirDevListTagName;
extern const QString ReadListTagName;
extern const QString WriteListTagName;
extern const QString ReportListTagName;
extern const QString ReadWriteListTagName;
extern const QString ReadRegListRegName;
extern const QString WriteRegListRegName;
extern const QString ReportListRegName;
extern const QString ReadWriteListRegName;
extern const QList<QString>m_RegListTagName;
extern const QList<QString>m_RegListRegName;


extern QHash<QString , QString >  m_RegIdPhyVirHash;//ID关联HASH KEY:PhyDev ID VAL：VirDev ID
extern QHash<QString , QString >  m_RegIdVirPhyHash;//ID关联HASH KEY: VirDev   ID VAL：PhyDev ID
extern QHash<QString, reg_dev_s>  m_RegIdRegInfoHash;//根据寄存器ID找实例化寄存器值

//class ComShareData : public QSharedMemory
//{

//};

class ComConfig
{
public:
    //返回静态类的指针
    static  ComConfig *instance() {
        static ComConfig cfg;
        return &cfg;
    }
//    ComConfig * instance(){
//        return this;
//    }
public:
    ComConfig();
    ~ComConfig();

//    QHash<QString , QString > m_RegIdPhyVirHash;//ID关联HASH KEY:PhyDev ID VAL：VirDev ID
//    QHash<QString , QString > m_RegIdVirPhyHash;//ID关联HASH KEY: VirDev   ID VAL：PhyDev ID
    //通过虚拟设备ID找到物理设备的寄存器ID

    //获取虚拟设备ID通过物理设备ID
     QString GetVirIdByPhyId(QString id)
    {
        qCDebug(ComConfigLog())<<__func__<<id;
        if( !m_RegIdPhyVirHash[id].length())
        {
            qCDebug(ComConfigLog())<<__func__<<id<<"不存在";
            dump_PhyVirHash();
            return  "";
        }
        else
        {

        }
        return m_RegIdPhyVirHash[id];
    }
    //通过虚拟ID找物理ID
    QString GetPhyIdByVirId(QString id)
    {
        qCDebug(ComConfigLog())<<__func__<<id;
        if( !m_RegIdVirPhyHash[id].length())
        {
            qCDebug(ComConfigLog())<<__func__<<id<<"不存在";
            dump_VirPhyHash();
            return  "";
        }
        else
        {
        }
        return m_RegIdVirPhyHash[id];
    }
public:
    //配置文件变化需要重新读取 槽函数
    static bool ReadXml(QString f_name = "./SUPER-COM.xml");
    static bool readAllDevList(const QDomElement &ele);
    //bool readVirDevList(QDomElement &ele);
private:
    static QList<Dev_s*>m_PhyDevList;//要接的物理设备的列表
    static QList<Dev_s*>m_VirDevList;//要转发的设备列表
    static QMap<QString , Dev_s>m_IdDevMap;//根据ID找设备
    static QDomDocument m_doc;//读取XML使用
    static QDomElement m_root;//根节点
    static super_com_info_s m_super_com_info;//通讯管理机信息
    static QList <reg_s>m_RegList;
    static QHash <QString, QList<Dev_s> >m_PortDevListHash;//保留端口和对应设备的Hash表信息
private:
    //清除目前的配置信息容器  ReadXml 会调用
    static void clearConfigInfoContain()
    {
        m_RegIdRegInfoHash.clear();
        m_RegIdPhyVirHash.clear();
        m_RegIdVirPhyHash.clear();
        m_PhyDevList.clear();
        m_VirDevList.clear();
        m_IdDevMap.clear();
        m_PortDevListHash.clear();
    }
    //获取根节点
    static QDomElement GetRootEle()
    {
        return m_root;
    }
public:

    static void dumpRegInfoHash();
    static void dump_PhyVirHash();
    static void dump_VirPhyHash();
    static void dump_PortDevListHash();

    static void test_dump()
    {
        dumpRegInfoHash();
        dump_PhyVirHash();
        dump_VirPhyHash();
    }

    //获取端口对应的设备列表的信息
    static QHash <QString, QList<Dev_s> > & GetPortDevListHash()
    {
        return m_PortDevListHash;
    }

    static QList<Dev_s*> *GetDevListByTagName(QString name)
    {
        if(name == PhyDevListTagName)
        {
            qCDebug(ComConfigLog())<<__FUNCTION__<<PhyDevListTagName;
            return &m_PhyDevList;
        }
        else if(name == VirDevListTagName)
        {
            qCDebug(ComConfigLog())<<__FUNCTION__<<VirDevListTagName;
            return &m_VirDevList;
        }
        qCWarning(ComConfigLog())<<__FUNCTION__<<"####ERROR####";
        return nullptr;
    }

    static QList<Dev_s*> &GetVirDevList()
    {
        return m_VirDevList;
    }

    static QList<Dev_s*> &GetPhyDevList()
    {
        return m_PhyDevList;
    }

    static QHash<QString , QString> &GetRegHashByName(QString name)
    {
        if(name == PhyDevListTagName)
        {
            return m_RegIdPhyVirHash;
        }
//        else if(name == VirDevListTagName)
        {
            return m_RegIdVirPhyHash;
        }
    }

    static reg_dev_s& GetRegInfoByID(QString &id)
    {
        return m_RegIdRegInfoHash[id];
    }
    //获取寄存器的数目，总数目
     int get_reg_num()
    {
        int num = 0;
        QMap<QString , Dev_s>::const_iterator i;
        for (i = m_IdDevMap.constBegin(); i != m_IdDevMap.constEnd(); ++i) {
            qCDebug(ComConfigLog())<<__func__<<"num:"<<num;
            num += dev_get_reg_num(i.value());
        }
        return  num;
    }
     static QList <reg_s> & get_all_reg_list()
     {
         return m_RegList;
     }
private:
    //返回设备的所有寄存器数目
     int dev_get_reg_num(const Dev_s &dev)
    {
        int num = 0;
        foreach(RegList_s list, dev.ReadRegList)
        {
            num += list.reg_list.length();
        }
        foreach(RegList_s list, dev.WriteRegList)
        {
            num += list.reg_list.length();
        }
        foreach(RegList_s list, dev.ReportRegList)
        {
            num += list.reg_list.length();
        }
        qCDebug(ComConfigLog())<<__func__<<"num:"<<num;
        return num;
    }
};

//extern ComConfig ComResData;
//Q_GLOBAL_STATIC(ComConfig, ComConfigData);


#endif // COMCONFIG_H
