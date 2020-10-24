#include "DevModelThread.h"

DevModelThread::DevModelThread(DeviceModel *p,  QList<Dev_s*> DevL, Dev_s * mb)
{
    m_DeviceModel = p;
    Dev_list = DevL;
    m_ModeDev = mb;
}


TestClass::TestClass()
{

}


TestClass::~TestClass()
{

}
