#include "PluginManager.h"
#include <QPluginLoader>
#include <QDir>

Q_LOGGING_CATEGORY(PluginManagerLog, "PluginManager.log")



PluginManager::PluginManager()
{
    qCDebug(PluginManagerLog())<<"构造";
}

PluginManager::~PluginManager()
{
    releasePlugin();
    qCDebug(PluginManagerLog())<<"析构";
}


void PluginManager::releasePlugin()
{
    QMapIterator<QString, QObject*> iter(m_plugins);
    while(iter.hasNext()) {
        iter.next();
        delete iter.value();
    }
    m_plugins.clear();
}


void PluginManager::loadAllPlugin()
{
    releasePlugin();

    QDir pluginsDir(QDir::currentPath());
    pluginsDir.cd(QLatin1String("lib"));

    foreach (QString szFileName, pluginsDir.entryList(QDir::Files)) {
#ifdef Q_OS_WIN
        if(!szFileName.endsWith(".dll"))
            continue;
#endif
#ifdef Q_OS_LINUX
        if(!szFileName.endsWith(".so"))
            continue;
#endif
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(szFileName));
        QObject *pluginObj = pluginLoader.instance();
        if (pluginObj) {
            QObject *plugin = qobject_cast<QObject *>(pluginObj);
            if (plugin) {
                QFileInfo fileInfo(szFileName);
                m_plugins.insert(fileInfo.baseName(), plugin);
            }
        }
    }
}

QObject *PluginManager::loadPluginPath(const QString &path, const QString &name)
{
    QDir pluginsDir(QDir::currentPath());
    pluginsDir.cd(path);
    QString szPluginName = name;

    foreach (QString szFileName, pluginsDir.entryList(QDir::Files)) {
#ifdef Q_OS_WIN
        if(!szFileName.endsWith(".dll"))
            continue;
#endif
#ifdef Q_OS_LINUX
        if(!szFileName.endsWith(".so"))
            continue;
#endif

#ifdef BUILD_BY_DEBUG
    #ifdef Q_OS_WIN
        szPluginName = name + "d";
    #endif
#endif
        QFileInfo fileInfo(szFileName);
        if(fileInfo.baseName().toLower() == szPluginName.toLower()) {

            qCDebug(PluginManagerLog())<<"fileInfo:"<<fileInfo.baseName()<<pluginsDir.absoluteFilePath(szFileName);
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(szFileName));
            QObject *pluginObj = pluginLoader.instance();
            if (pluginObj != nullptr) {
//                QObject *plugin = qobject_cast<QObject *>(pluginObj);
                QObject *plugin = pluginObj;
                if (plugin != nullptr) {
                    qCDebug(PluginManagerLog())<<"loadPlugin:"<<name<<"OK";
                    return plugin;
                }
                else
                {
                    qCDebug(PluginManagerLog())<<"loadPlugin:"<<name<<"but null";
                }
            }
        }
    }
    qCDebug(PluginManagerLog())<<"loadPlugin:"<<name<<"open error";

    return Q_NULLPTR;
}

QObject* PluginManager::loadPlugin(const QString &name)
{

    QDir pluginsDir(QDir::currentPath());
    pluginsDir.cd(QLatin1String("lib"));
    QString szPluginName = name;

    foreach (QString szFileName, pluginsDir.entryList(QDir::Files)) {
#ifdef Q_OS_WIN
        if(!szFileName.endsWith(".dll"))
            continue;
#endif
#ifdef Q_OS_LINUX
        if(!szFileName.endsWith(".so"))
            continue;
#endif

#ifdef BUILD_BY_DEBUG
    #ifdef Q_OS_WIN
        szPluginName = name + "d";
    #endif
#endif
        QFileInfo fileInfo(szFileName);
        if(fileInfo.baseName().toLower() == szPluginName.toLower()) {

            qCDebug(PluginManagerLog())<<"fileInfo:"<<fileInfo.baseName()<<pluginsDir.absoluteFilePath(szFileName);
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(szFileName));
            QObject *pluginObj = pluginLoader.instance();
            if (pluginObj != nullptr) {
//                QObject *plugin = qobject_cast<QObject *>(pluginObj);
                QObject *plugin = pluginObj;
                if (plugin != nullptr) {
                    qCDebug(PluginManagerLog())<<"loadPlugin:"<<name<<"OK";
                    return plugin;
                }
                else
                {
                    qCDebug(PluginManagerLog())<<"loadPlugin:"<<name<<"but null";
                }
            }
        }
    }
    qCDebug(PluginManagerLog())<<"loadPlugin:"<<name<<"open error";

    return Q_NULLPTR;
}


QObject* PluginManager::getPlugin(const QString &name)
{
    QObject *pDevPlugin = Q_NULLPTR;
    if(name == "") return Q_NULLPTR;
    if(m_plugins.contains(name)) {
        pDevPlugin = m_plugins.value(name);
    }
    else {
        pDevPlugin = loadPlugin(name);
        if (pDevPlugin) {
            m_plugins.insert(name, pDevPlugin);
        }
    }
    return pDevPlugin;
}
