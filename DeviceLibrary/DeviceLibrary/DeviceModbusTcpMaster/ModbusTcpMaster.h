#ifndef MODBUSTCPMASTER_H
#define MODBUSTCPMASTER_H

#include <QGenericPlugin>

class ModbusTcpMaster : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceModbusTcpMaster.json")

public:
    explicit ModbusTcpMaster(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // MODBUSTCPMASTER_H
