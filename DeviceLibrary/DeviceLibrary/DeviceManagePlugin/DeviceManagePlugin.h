#ifndef DEVICEMANAGEPLUGIN_H
#define DEVICEMANAGEPLUGIN_H

#include <QGenericPlugin>

class DeviceManagePlugin : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceManagePlugin.json")

public:
    explicit DeviceManagePlugin(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // DEVICEMANAGEPLUGIN_H
