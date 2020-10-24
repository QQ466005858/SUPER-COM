#include "CS101Client.h"

CS101Client::CS101Client(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *CS101Client::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
