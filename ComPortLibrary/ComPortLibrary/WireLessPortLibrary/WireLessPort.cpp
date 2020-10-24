#include "WireLessPort.h"

WireLessPort::WireLessPort(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *WireLessPort::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
