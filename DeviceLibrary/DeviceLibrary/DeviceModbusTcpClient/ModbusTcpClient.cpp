#include "ModbusTcpClient.h"

ModbusTcpClient::ModbusTcpClient(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *ModbusTcpClient::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
