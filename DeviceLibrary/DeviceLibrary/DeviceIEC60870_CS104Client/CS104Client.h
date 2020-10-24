#ifndef CS104CLIENT_H
#define CS104CLIENT_H

#include <QGenericPlugin>

class CS104Client : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceIEC60870_CS104Client.json")

public:
    explicit CS104Client(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // CS104CLIENT_H
