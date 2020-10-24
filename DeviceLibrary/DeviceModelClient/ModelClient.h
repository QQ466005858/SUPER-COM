#ifndef MODELCLIENT_H
#define MODELCLIENT_H

#include <QObject>
#include <DeviceModel.h>


/*
 * ModelClient 设备模型 适用于 modbus client 为 从机设备模型 主机问 从机回答
*/
class ModelClient : public DeviceModel
{
    public:
    virtual ~ModelClient(){};



};



QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(ModelClient, "DeviceLibrary.ModelClient");
QT_END_NAMESPACE



#endif // MODELCLIENT_H
