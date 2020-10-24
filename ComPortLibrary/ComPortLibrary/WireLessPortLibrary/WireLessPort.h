#ifndef WIRELESSPORT_H
#define WIRELESSPORT_H

#include <QGenericPlugin>

class WireLessPort : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "WireLessPortLibrary.json")

public:
    explicit WireLessPort(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // WIRELESSPORT_H
