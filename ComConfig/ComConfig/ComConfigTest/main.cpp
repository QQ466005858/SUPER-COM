#include <QCoreApplication>
#include <ComConfig.h>
#include <QLoggingCategory>
#include <QDebug>

#include <ComShareMemory.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QLoggingCategory::setFilterRules(QStringLiteral("ComConfig.log = true"));

    qDebug()<<"hello";

    ComConfig::instance()->ReadXml("I:/Project/MYSELF/0001-SUPER-COM/00-QT/SUPER-COM/SUPER-COM.xml");

    ComConfig::dump_PortDevListHash();


    return a.exec();
}
