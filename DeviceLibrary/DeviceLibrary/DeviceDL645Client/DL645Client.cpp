#include "DL645Client.h"

DL645Client::DL645Client(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *DL645Client::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
