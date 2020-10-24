#include <QCoreApplication>
#include <PluginManager.h>
#include <QDebug>
#include <QDir>
#include <ComPort.h>
#include <SerialPort.h>


#include <QLoggingCategory>
#include <QDebug>




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QLoggingCategory::setFilterRules(QStringLiteral("ComPortLibrary.SerialPort.log = true"));
    qDebug()<<"current path:"<<QDir::currentPath();
    ComPort *port = qobject_cast<ComPort *>(PluginManager::getInstance()->loadPlugin("SerialPortLibrary"));
    if(port != nullptr)
    {
        qDebug()<<"dll open ok";

        QStringList list;
        list.append("9600");
        list.append("N");
        list.append("8");
        list.append("1");
        bool res = port->open("COM1", list);
        if(res)
        {
            QByteArray data;
            data.append("123456789");
            port->write(data, 100);
            port->close();
        }
        else
        {
            qDebug()<<"port open error:"<<res;
        }
    }
    else
    {
        qDebug()<<"dll open error";
    }
    qDebug()<<"test finshed";
    return a.exec();
}
