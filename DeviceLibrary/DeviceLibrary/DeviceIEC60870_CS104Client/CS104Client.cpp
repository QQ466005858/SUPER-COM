#include "CS104Client.h"

CS104Client::CS104Client(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *CS104Client::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
