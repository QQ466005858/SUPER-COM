#ifndef MODBUSTCPCLIENT_H
#define MODBUSTCPCLIENT_H

#include <QGenericPlugin>

class ModbusTcpClient : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceModbusTcpClient.json")

public:
    explicit ModbusTcpClient(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // MODBUSTCPCLIENT_H
