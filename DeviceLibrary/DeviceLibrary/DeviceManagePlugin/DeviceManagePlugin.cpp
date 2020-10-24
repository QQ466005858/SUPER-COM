#include "DeviceManagePlugin.h"

DeviceManagePlugin::DeviceManagePlugin(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *DeviceManagePlugin::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
