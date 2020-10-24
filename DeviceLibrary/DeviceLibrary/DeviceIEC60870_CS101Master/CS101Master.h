#ifndef CS101MASTER_H
#define CS101MASTER_H

#include <QGenericPlugin>

class CS101Master : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceIEC60870_CS101Master.json")

public:
    explicit CS101Master(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // CS101MASTER_H
