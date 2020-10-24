#include "DevModelThread.h"

DevModelThread::DevModelThread(DeviceModel *p,  QList<Dev_s*> DevL, Dev_s * mb,  ComConfig*com)
{
    m_DeviceModel = p;
    Dev_list = DevL;
    m_ModeDev = mb;
    m_com = com;
}


TestClass::TestClass()
{

}


TestClass::~TestClass()
{

}
