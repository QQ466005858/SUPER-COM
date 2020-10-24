#ifndef COMPORT_H
#define COMPORT_H

#include <QObject>

// 端口类型
typedef enum _PortType {
    PORT_NONE = 0,
    PORT_SERIAL = 1,
    PORT_NET = 2,
    PORT_RF = 3,
    PORT_RESERVE = 255 // 预留
}TPortType;


class ComPort
{
public:
    virtual ~ComPort() {};
    virtual bool open(QString port, QStringList args) = 0;
    virtual bool isOpen() = 0;
    virtual bool reOpen() = 0;
    virtual int read(QByteArray & rec, int ms) = 0;
    virtual int read(unsigned char *buf, int len, int ms) = 0;
    virtual int write(unsigned char *buf, int len, int ms) = 0;
    virtual int write(QByteArray buf, int ms) = 0;
    virtual void clear_read() = 0;
    virtual bool close() = 0;
    virtual TPortType getPortType() = 0;
};

QT_BEGIN_NAMESPACE
#define ComPortPluginInterface_IID "ComPortLibrary.ComPortLibrary.ComPort"
Q_DECLARE_INTERFACE(ComPort, ComPortPluginInterface_IID);
QT_END_NAMESPACE


#endif // COMPORT_H
