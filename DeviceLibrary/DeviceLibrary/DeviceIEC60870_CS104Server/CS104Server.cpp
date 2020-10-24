#include "CS104Server.h"

CS104Server::CS104Server(QObject *parent)
    : QGenericPlugin(parent)
{
}

QObject *CS104Server::create(const QString &name, const QString &spec)
{
    //static_assert(false, "You need to implement this function");
}
