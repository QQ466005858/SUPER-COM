#ifndef NETPORT_H
#define NETPORT_H
#include <QObject>
#include <ComPort.h>
#include <QTimer>
#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QtNetwork>

class NetPort : public QObject, ComPort
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ComPortPluginInterface_IID FILE "NetPortLibrary.json")
    Q_INTERFACES(ComPort)
public:
    NetPort(QString sIp, int tPort);
    NetPort(){};
    ~NetPort();
public:
    QTcpSocket* getSocket();
    bool open(QString port, QStringList args) Q_DECL_OVERRIDE;
    bool isOpen() Q_DECL_OVERRIDE;
    bool reOpen() Q_DECL_OVERRIDE;
    int read(QByteArray & rec, int ms) Q_DECL_OVERRIDE;
    int read(unsigned char *buf, int len, int ms) Q_DECL_OVERRIDE;
    int write(unsigned char *buf, int len, int ms) Q_DECL_OVERRIDE;
    int write(QByteArray buf, int ms) Q_DECL_OVERRIDE;
    bool close() Q_DECL_OVERRIDE;
    void clear_read() Q_DECL_OVERRIDE;
    TPortType getPortType() Q_DECL_OVERRIDE;



private:
    QTcpSocket *client;
    int port_;
    QString ip_;
};

#endif // NETPORT_H
