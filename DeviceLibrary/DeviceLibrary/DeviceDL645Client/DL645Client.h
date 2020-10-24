#ifndef DL645CLIENT_H
#define DL645CLIENT_H

#include <QGenericPlugin>

class DL645Client : public QGenericPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "DeviceDL645Client.json")

public:
    explicit DL645Client(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // DL645CLIENT_H
