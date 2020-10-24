#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <ComPort.h>
#include <QSerialPort>

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(SerialPortLog)


class SerialPort : public QObject, ComPort
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ComPortPluginInterface_IID FILE "SerialPortLibrary.json")
    Q_INTERFACES(ComPort)
public:
    SerialPort();
    ~SerialPort() Q_DECL_OVERRIDE;

public:
    bool open(QString port, QStringList args) Q_DECL_OVERRIDE;
    bool reOpen() Q_DECL_OVERRIDE;
    int read(unsigned char *buf, int len, int ms) Q_DECL_OVERRIDE;
    int write(unsigned char *buf, int len, int ms) Q_DECL_OVERRIDE;
    bool close() Q_DECL_OVERRIDE;
    TPortType getPortType() Q_DECL_OVERRIDE;
    bool isOpen()Q_DECL_OVERRIDE;
    int write(QByteArray buf, int ms) Q_DECL_OVERRIDE;
    int read(QByteArray & rec, int ms) Q_DECL_OVERRIDE;
    void clear_read()Q_DECL_OVERRIDE;
private:
    QSerialPort *serialPortPtr_;
    QByteArray buf_;
    void readAll();
};

#endif // SERIALPORT_H
