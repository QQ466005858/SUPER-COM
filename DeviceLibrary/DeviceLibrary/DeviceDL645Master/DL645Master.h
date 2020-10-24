#ifndef DL645MASTER_H
#define DL645MASTER_H

#include <QGenericPlugin>

class DL645Master : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceDL645Master.json")

public:
    explicit DL645Master(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // DL645MASTER_H
