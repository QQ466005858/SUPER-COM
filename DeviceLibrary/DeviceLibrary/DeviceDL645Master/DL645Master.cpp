#include "DL645Master.h"

DL645Master::DL645Master(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *DL645Master::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
