#ifndef CS101CLIENT_H
#define CS101CLIENT_H

#include <QGenericPlugin>

class CS101Client : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceIEC60870_CS101Client.json")

public:
    explicit CS101Client(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // CS101CLIENT_H
