#include <QCoreApplication>
#include <QDebug>

#include "ComConfig.h"
#include "ComShareMemory.h"

class TestClassA;

typedef int (TestClassA::*pfun)();

pfun pf_protected1 = NULL;

class TestClassA : public QObject
{
public:
    TestClassA(){};
    ~TestClassA(){};
    int val;
    int test;
    int next;


    char tmp[16];
    void func(int a, int b)
    {
        qDebug()<<__func__<<a<<b;
    }
//    static int a_static_fun()
//    {
//        pf_protected1 = &TestClassA::func;
//        return -1;
//    }

};

#define CONFIG_FILE_PATH  "I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    TestClassA
//    TestClassA *pTest = new TestClassA();
//    qDebug()<<__func__<<"TestClassA size:"<<sizeof(TestClassA);
//    qDebug()<<__func__<<"pTest size:"<<sizeof(pTest);
//    qDebug()<<__func__<<"*pTest size:"<<sizeof(*pTest);
//    pTest->func(1, 2);
//    qDebug()<<__func__<<"*pTest addr:"<<pTest;
//    printf("TestClassA %p \n", pTest);
//    printf("TestClassA.val %p \n", &pTest->val);
//    printf("TestClassA.test %p \n", &pTest->test);
//    printf("TestClassA.tmp %p \n", pTest->tmp);
//    printf("TestClassA.tmp %p \n", &pTest->tmp[15]);
//    printf("TestClassA::func %p \n", &TestClassA::func);
//    printf("TestClassA::val %p \n", &TestClassA::val);
//    printf("TestClassA::test %p \n", &TestClassA::test);
//    printf("TestClassA::next %p \n", &TestClassA::next);
//    int test_tmp_int_a = 0;
//    printf("test_tmp_int_a %p \n", &test_tmp_int_a);
//    TestClassA Test;
//    qDebug()<<__func__<<"Test size:"<<sizeof(Test);
//    qDebug()<<__func__<<"Test addr:"<<&Test;
//    qDebug()<<"\n---------------------------\n";
//    Reg tmp_reg();
//    qDebug()<<__func__<<"Reg size:"<<sizeof(Reg);
//    qDebug()<<__func__<<"QObject size:"<<sizeof(QObject);
//    qDebug()<<"\n---------------------------\n";

//    ComShareMemory *pMem = ComShareMemory::instance();
//    ComConfig *pComConfig = ComConfig::instance();
//    pComConfig->ReadXml(CONFIG_FILE_PATH);

//    QList<Dev_s*> & DevList = pComConfig->GetPhyDevList();

//    foreach(Dev_s *pDev, DevList)
//    {
//        pMem->creat_dev_info_mem(*pDev);
//    }
    QString key;
//    key.fromUtf8("SerialPort,COM1,9600,N,8,1");
    key = "SerialPort,COM1,9600,N,8,1";
    QSharedMemory shareMem;
    shareMem.setKey(key);

    shareMem.attach();

    if(shareMem.isAttached() == false)
    {
        qDebug()<<"shareMeme Data Attached Failed\n";
        return -1;
    }

    shareMem.lock();
    qDebug()<<"\n---------------------------\n";

//    Dev_s * dev = static_cast<Dev_s*>(shareMem.data());
    Dev_s * dev = (Dev_s*)shareMem.data();

    if(dev == nullptr)
    {
        qDebug()<<"not find shareMeme Data\n";
        return -1;
    }
    qDebug()<<dev->id<<dev->name<<dev->port<<dev->DeviceLibrary;
    shareMem.unlock();
    shareMem.detach();
    qDebug()<<"\n---------------------------\n";

    return a.exec();
}
