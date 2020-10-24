#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "PluginManager_global.h"
#include <QObject>
#include <QMap>


#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(PluginManagerLog)
//PLUGINMANAGER_EXPORT
class PluginManager
{
public:
    static PluginManager *getInstance() {
        static PluginManager instance;
        return &instance;
    }

private:
    PluginManager();
    ~PluginManager();



public:
    void loadAllPlugin();
    QObject *loadPluginPath(const QString &path, const QString &name);
    QObject* loadPlugin(const QString &name);
    QObject* getPlugin(const QString &name);
    void releasePlugin();

public:
    //------name-------plugin
    QMap<QString, QObject*> m_plugins;
};

#endif // PLUGINMANAGER_H
