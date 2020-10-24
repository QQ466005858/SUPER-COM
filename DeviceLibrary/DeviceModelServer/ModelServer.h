#ifndef MODELSERVER_H
#define MODELSERVER_H

#include <DeviceModel.h>

/*
 * ModelServer 设备模型 适用于 modbus server 类 为 主站模式 轮询 设备
*/
class ModelServer : public DeviceModel
{
    public:
        virtual ~ModelServer(){};
};

#endif // MODELSERVER_H
