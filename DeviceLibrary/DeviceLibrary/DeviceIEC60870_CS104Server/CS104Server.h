#ifndef CS104SERVER_H
#define CS104SERVER_H

#include <QGenericPlugin>

class CS104Server : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceIEC60870_CS104Server.json")

public:
    explicit CS104Server(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // CS104SERVER_H
